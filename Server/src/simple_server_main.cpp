#include "lib/ServerSocket.h"
#include "lib/SocketException.h"
#include <string>
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

#include <fstream>
#include <sstream>

// Include the rest of our code!
#include "lib/detectObject.h"       // Easily detect faces or eyes (using LBP or Haar Cascades).
#include "lib/preprocessFace.h"     // Easily preprocess face images, for face recognition.
#include "lib/recognition.h"     // Train the face recognition system and recognize a person from an image.

//#include "lib/ImageUtils.h"      // Shervin's handy OpenCV utility functions.

using namespace cv;
using namespace std;


// Cascade Classifier file, used for Face Detection.
//const char *faceCascadeFilename = "lbpcascade_frontalface.xml";     // LBP face detector.
const char *faceCascadeFilename = "include/haarcascade_frontalface_alt.xml";  // Haar face detector.
const char *eyeCascadeFilename1 = "include/haarcascade_lefteye_2splits.xml";   // Best eye detector for open-or-closed eyes.
const char *eyeCascadeFilename2 = "include/haarcascade_righteye_2splits.xml";   // Best eye detector for open-or-closed eyes.
//const char *eyeCascadeFilename1 = "haarcascade_mcs_lefteye.xml";       // Good eye detector for open-or-closed eyes.
//const char *eyeCascadeFilename2 = "haarcascade_mcs_righteye.xml";       // Good eye detector for open-or-closed eyes.
//const char *eyeCascadeFilename1 = "haarcascade_eye.xml";               // Basic eye detector for open eyes only.
//const char *eyeCascadeFilename2 = "haarcascade_eye_tree_eyeglasses.xml"; // Basic eye detector for open eyes if they might wear glasses.


// Set the desired face dimensions. Note that "getPreprocessedFace()" will return a square face.
const int faceWidth = 72;
const int faceHeight = faceWidth;

const bool preprocessLeftAndRightSeparately = true;

const int numOfModels = 3;
const double maxDistance = 1000.0;

const double coef[3] =
{
  848.836,
  77.0003,
  69.8203 * 2.0
};

const string modelFile[numOfModels] = 
{
  "models/eigenModel.xml",
  "models/fisherModel.xml",
  "models/lbphModel.xml"
};

Ptr<FaceRecognizer> model[numOfModels] =
{
  cv::createEigenFaceRecognizer(),
  cv::createFisherFaceRecognizer(),
  createLBPHFaceRecognizer()
};

const char *dbAddress = "/opt/lampp/htdocs/fr/db/db.dat";

int m_numPersons = 0;

CascadeClassifier faceCascade;
CascadeClassifier eyeCascade1;
CascadeClassifier eyeCascade2;

ofstream logFile;
ofstream dbFile;

    //const int height = 100;

// Load the face and 1 or 2 eye detection XML classifiers.
void initDetectors()
{
    // Load the Face Detection cascade classifier xml file.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!samples for training face detection classifier
        faceCascade.load(faceCascadeFilename);
    } catch (cv::Exception &e) {}
    if ( faceCascade.empty() ) {
        cerr << "ERROR: Could not load Face Detection cascade classifier [" << faceCascadeFilename << "]!" << endl;
        cerr << "Copy the file from your OpenCV data folder (eg: 'C:\\OpenCV\\data\\lbpcascades') into this WebcamFaceRec folder." << endl;
        exit(1);
    }
    cout << "Loaded the Face Detection cascade classifier [" << faceCascadeFilename << "]." << endl;

    // Load the Eye Detection cascade classifier xml file.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
        eyeCascade1.load(eyeCascadeFilename1);
    } catch (cv::Exception &e) {}
    if ( eyeCascade1.empty() ) {
        cerr << "ERROR: Could not load 1st Eye Detection cascade classifier [" << eyeCascadeFilename1 << "]!" << endl;
        cerr << "Copy the file from your OpenCV data folder (eg: 'C:\\OpenCV\\data\\haarcascades') into this WebcamFaceRec folder." << endl;
        exit(1);
    }
    cout << "Loaded the 1st Eye Detection cascade classifier [" << eyeCascadeFilename1 << "]." << endl;

    // Load the Eye Detection cascade classifier xml file.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
        eyeCascade2.load(eyeCascadeFilename2);
    } catch (cv::Exception &e) {}
    if ( eyeCascade2.empty() ) {
        cerr << "Could not load 2nd Eye Detection cascade classifier [" << eyeCascadeFilename2 << "]." << endl;
        // Dont exit if the 2nd eye detector did not load, because we have the 1st eye detector at least.
        //exit(1);
    }
    else
        cout << "Loaded the 2nd Eye Detection cascade classifier [" << eyeCascadeFilename2 << "]." << endl;
}

    static Mat processImage(Mat &originalImage)
    {

        Mat displayedFrame;

        originalImage.copyTo(displayedFrame);
        
        // Run the face recognition system on the camera image. It will draw some things onto the given image, so make sure it is not read-only memory!
        int identity = -1;

        // Find a face and preprocess it to have a standard size and contrast & brightness.
        Rect faceRect;  // Position of detected face.
        Rect searchedLeftEye, searchedRightEye; // top-left and top-right regions of the face, where eyes were searched.
        Point leftEye, rightEye;    // Position of the detected eyes.

        cout<<displayedFrame.size()<<endl;
        Mat preprocessedFace = getPreprocessedFace(displayedFrame, faceWidth, faceCascade, eyeCascade1, eyeCascade2, preprocessLeftAndRightSeparately, &faceRect, &leftEye, &rightEye, &searchedLeftEye, &searchedRightEye);

        //imshow("test", preprocessedFace);
        //waitKey(0);

        bool gotFaceAndEyes = false;
        if (preprocessedFace.data)
            gotFaceAndEyes = true;
	cout<<"gotFaceAndEyes:"<<gotFaceAndEyes<<endl;
        return preprocessedFace;
    }

    static Mat toGrayscale(InputArray _src) {
        Mat src = _src.getMat();
        // only allow one channel
        if(src.channels() != 1) {
            CV_Error(CV_StsBadArg, "Only Matrices with one channel are supported");
        }
        // create and return normalized image
        Mat dst;
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        return dst;
    }

    static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, bool mirror = false)
    {
        dbFile.open (dbAddress);
        char separator = ';';

        Mat orImage;
        Mat prImage;
        Mat mirrorImage;

        int found=0;
        int notFound=0;

        std::ifstream file(filename.c_str(), ifstream::in);
        if (!file) {
            string error_message = "No valid input file was given, please check the given filename.";
            CV_Error(CV_StsBadArg, error_message);
        }
        string line, path, classlabel;
        while (getline(file, line)) {
            stringstream liness(line);
            getline(liness, path, separator);
            getline(liness, classlabel);
            
            if(path.find(".gif")!=string::npos)
              continue;
            if(!path.empty() && !classlabel.empty()) {
                try {
                  orImage = imread(path, 0);
                  prImage = processImage(orImage);
                }
                catch (cv::Exception& e)
                {
                  cerr << "Error oppening file " << path << ". Reason: " << e.msg << endl;
                  continue;
                }
                
                if(prImage.data)
                {
                    string origAddress = format("/opt/lampp/htdocs/fr/db/orig/%d.png", found);
                    imwrite(origAddress, orImage);

                    //cout << format("/var/www/fr/db/prepared/%d", found);
                    string preparedAddress = format("/opt/lampp/htdocs/fr/db/prepared/%d.png", found);

                    imwrite(preparedAddress, prImage);

                    //cout << "found face: " << path << endl;
                    images.push_back(prImage);
                    labels.push_back(atoi(classlabel.c_str()));

                    if(mirror)
                    {
                      flip(prImage, mirrorImage, 1);
                      images.push_back(mirrorImage);
                      labels.push_back(atoi(classlabel.c_str()));
                    }

                    dbFile << origAddress << ";" << preparedAddress << ";" << atoi(classlabel.c_str()) << endl;
                    found++;
                }
                else
                {
                  notFound++;
                  cout << "not found face: " << path << endl;
                }
            }
        }
        cout << "found: " << found << ", not found: " << notFound << endl;
    }

    static bool train(const string& fn_csv, string& reply)
    {

        model[0] = createEigenFaceRecognizer();
        model[1] = createFisherFaceRecognizer();
        model[2] = createLBPHFaceRecognizer();

	cout<<fn_csv;
        //string fn_csv = "~/att.txt";
        // These vectors hold the images and corresponding labels.
        vector<Mat> images;
        vector<int> labels;
        // Read in the data. This can fail if no valid
        // input filename is given.
        try {
            read_csv(fn_csv, images, labels, true);
        } catch (cv::Exception& e) {
            cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
            // nothing more we can do
            exit(1);
        }

        for (int i = 0; i<numOfModels; i++)
        {
          model[i]->train(images, labels);
          model[i]->save(modelFile[i]);
          cout << "model[" << i << "] trained." << endl;
        }

        reply = "success\n";
        return true;

    }

    void recognize(const Mat& imgFile, int& predictedLabel, double& confidence, string &msg, int singleModel = -1)
    {
      if(singleModel == -1) 
      {
        vector<int> predicted;
        int currPred = -1;      
        double sum;
        double currDistance;
        double conf[numOfModels];
        confidence = maxDistance;

        for (int i = 0; i<numOfModels; i++)
        {
          currPred = model[i]->predict(imgFile);
          if( find( predicted.begin(), predicted.end(), currPred ) == predicted.end() )
            predicted.push_back(currPred);
        }

        for (vector<int>::iterator it = predicted.begin(); it != predicted.end(); it++)
        {
          for(int i = 0; i < numOfModels; i++)
          {
            model[i]->predict(imgFile, *it, conf[i]);
            if(conf[i]/coef[i] < confidence)
            {
              confidence = conf[i]/coef[i];
              predictedLabel = *it;
            }
          }

          sort(conf, conf + 3);
          sum = 0.0;

          for(int i = 0; i < numOfModels-1; i++)
            sum += conf[i];

          currDistance = sum / (double)(numOfModels-1);
          if(currDistance < confidence)
          {
            confidence = currDistance;
            predictedLabel = *it;
          }
        }

        if (confidence == maxDistance)
          predictedLabel = -1;
      }
      else
      {
        confidence = 0.0;
        model[singleModel]->predict(imgFile, predictedLabel, confidence);
      }

    }

    static double multipleRecognize(const string& fn_csv)
    {

        // These vectors hold the images and corresponding labels.
        vector<Mat> images;
        vector<int> labels;
        double confSum = 0;
        double avgConf;

        string msg;
        // Read in the data. This can fail if no valid
        // input filename is given.
        try {
            read_csv(fn_csv, images, labels);
        } catch (cv::Exception& e) {
            cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
            // nothing more we can do
            exit(1);
        }

        int predictedLabel;
        double confidence;

        int correctP = 0; // num of correct predictions
        int wrongP = 0; // num of wrong predictions

        vector<int>::iterator itL = labels.begin();     

        cout << endl << "All: " << endl;

        correctP = 0;
        wrongP = 0;
        confSum = 0;

        itL = labels.begin();        
        for(vector<Mat>::iterator itI = images.begin() ; itI != images.end(); itI++)
        {
          recognize(*itI, predictedLabel, confidence, msg);

          if (predictedLabel == *itL)
          {
            correctP++;
            confSum += confidence;
          }
          else
          {
            wrongP++;
            //cout << "wrong, predicted " << predictedLabel << ", actual label: " << *itL << ", confidence: "<< confidence << ", message: " << msg << endl;
          }

          itL++;

        }
        avgConf = confSum / correctP;
        cout << "correct: " << correctP << ", wrong: " << wrongP << ", avg confidence: " << avgConf << endl;

        double score = ((double)correctP)/((double)(correctP+wrongP));

        return score;

    }

    static void append(const Mat& imgFile, const int testLabel, string& reply)
    {
      
      vector<Mat> newImages;
      vector<int> newLabels;

      newImages.push_back(imgFile);
      newLabels.push_back(testLabel);

      model[2]->update(newImages, newLabels);

      model[2]->save(modelFile[2]);

      stringstream ss;
      ss << testLabel;
      cout << "label: " << testLabel << "\n" << flush;

      reply = "success! personID = " + ss.str();

    }
    

int main ( int argc, char *argv[] )
{
  std::cout << "running....\n";

  logFile.open ("logs/log.txt");
  logFile << "Server started.\n";
  int port;

  if(argc == 2)
  {
    istringstream ss1(argv[1]);
    ss1 >> port;
  }
  else
    port = 30000;  

  cout << "Port: " << port << endl;  

  Mat imgFile;
  Mat orImage;

  for (int i = 0; i<numOfModels; i++)
  {
    ifstream f(modelFile[i].c_str());
    if(f.good());
      model[i]->load(modelFile[i]);
  }
  
  initDetectors();
  try
    {
      // Create the socket
      ServerSocket server ( port );

      while ( true )
    {
      wait:

      ServerSocket new_sock;
      server.accept ( new_sock );
      
      try
        {
          while ( true )
            {
              size_t found;

              char action;
              string fileName;
              string message;
              string reply;
              int label;

              new_sock >> message;

              action = message[0];
              logFile << "Action: " << action << "\n";
	      
              if(action=='A')
              {
		
                found = message.find(";");
                fileName = message.substr(1, found-1);
                label = atoi((message.substr(found+1)).c_str());
              }
              else
                fileName = message.substr(1);
              fileName = "/opt/lampp/htdocs/fr/upload/" + fileName;

              cout << "file: " << fileName << "\n";

              cout << flush;
	      
              if(action != 'T' && action != 'M')
              {
		 ifstream f(fileName.c_str());
		  cout<<"good?:"<< f.good()<<endl;
                orImage = cv::imread(fileName, IMREAD_GRAYSCALE);
		cout<<"cols:"<<orImage.cols<<endl;
                imgFile = processImage(orImage);
		
                if(imgFile.empty())
                {
                  new_sock << "{\"success\":false,\"exception\":\"Face not found!\"}";
                  logFile << "Nije pronadjeno lice.\n";
                  goto wait;
                }
                
                //imwrite( "Gray_Image.jpg", imgFile );
//                 return 0;

                logFile << "Img read. \n" << flush;
              }
              
              if(action == 'T') // Train
              {
                cout << "Training on file "<<fileName<<endl;
                train(fileName, reply);

              }
              else if(action == 'M') // Multiple recognize
              {
                double score;
                cout << "Multiple recognize!\n";
                score = multipleRecognize(fileName);
                cout << score;
                reply = format("Score: %f.\n", score);

              }                
              else if(action == 'R') // Recognize
              {
                int predictedLabel;
                double confidence;
                string msg;

                cout << "Recognize!" << endl;
                recognize(imgFile, predictedLabel, confidence, msg);
                cout << "poruka" << msg << endl;

//                 reply = format("Predicted class = %d / Confidence distance= %f.\n", predictedLabel, confidence);
		reply=format("{\"success\":1,\"predicted\":%d,\"confidence\":%f}",predictedLabel,1-confidence);
                //cout << reply;
              }                
              else if(action == 'A') // Append to training model
              {
                cout << "Append!\n";
		
                append(imgFile, label, reply);
              }                

              new_sock << reply;
              cout << "\n Sent back: " << reply << flush;

            }
        }
      catch ( SocketException& ) {}

    }
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  logFile.close();
  dbFile.close();

  return 0;
}
