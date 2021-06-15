/*
ML: Predicting houseprice using locally weighted  regression
*/


#include <iostream>
#include <math.h>

#include <conio.h>

using namespace std;

struct TrainingSet{
	float area, price, noOfRooms;
	TrainingSet(){}
	TrainingSet(float a, int n, float p){
		area = a;
		noOfRooms = n;
		price = p;
	}
};
TrainingSet trainingData[] = {
		TrainingSet( 2104,3,399 ),
		TrainingSet( 1600,3,329 ),
		TrainingSet( 2400,3,369 ),
		TrainingSet( 1416,2,232 ),
		TrainingSet( 3000,4,539 ),
		TrainingSet( 1985,4,299 ),
		TrainingSet( 1534,3,314 ),
		TrainingSet( 1427,3,198 ),
		TrainingSet( 1380,3,212 ),
		TrainingSet( 1494,3,242 ),
		TrainingSet( 1940,4,239 ),
		TrainingSet( 2000,3,347 ),
		TrainingSet( 1890,3,329 ),
		TrainingSet( 4478,5,699 ),
		TrainingSet( 1268,3,259 ),
		TrainingSet( 2300,4,449 ),
		TrainingSet( 1320,2,299 ),
		TrainingSet( 1236,3,199 ),
		TrainingSet( 2609,4,499 ),
		TrainingSet( 3031,4,599 ),
		TrainingSet( 1767,3,252 ),
		TrainingSet( 1888,2,255 ),
		TrainingSet( 1604,3,242 ),
		TrainingSet( 1962,4,259 ),
		TrainingSet( 3890,3,573 ),
		TrainingSet( 1100,3,249 ),
		TrainingSet( 1458,3,464 ),
		TrainingSet( 2526,3,469 ),
		TrainingSet( 2200,3,475 ),
		TrainingSet( 2637,3,299 ),
		TrainingSet( 1839,2,349 ),
		TrainingSet( 1000,1,169 ),
		TrainingSet( 2040,4,314 ),
		TrainingSet( 3137,3,579 ),
		TrainingSet( 1811,4,285 ),
		TrainingSet( 1437,3,249 ),
		TrainingSet( 1239,3,229 ),
		TrainingSet( 2132,4,345 ),
		TrainingSet( 4215,4,549 ),
		TrainingSet( 2162,4,287 ),
		TrainingSet( 1664,2,368 ),
		TrainingSet( 2238,3,329 ),
		TrainingSet( 2567,4,314 ),
		TrainingSet( 1200,3,299 ),
		TrainingSet( 852,2,179 ),
		TrainingSet( 1852,4,390 ),
		TrainingSet( 1203,3,239 ),

	};



int main(){
	int nTraining = sizeof(trainingData)/sizeof(trainingData[0]);
	float w0, w1, w2, alpha, desiredError, learningRate;
	float weights[nTraining];
	
	TrainingSet testData;
	cout<<"Enter area:  ";
	cin>>testData.area;
	cout<<"\nEnter no. of rooms :  ";
	cin>>testData.noOfRooms;
	
	w0 = 0.5;	w1 = 0.2; w2 = 1;	alpha = 200;	desiredError = 0.01;	learningRate = 0.00000001;
	
	for(int i = 0; i < nTraining; ++i){
		float a = pow(trainingData[i].area - testData.area, 2) + pow(trainingData[i].noOfRooms - testData.noOfRooms,2);
		float b = (-2 * alpha * alpha);
		float c = exp(a/b);
		if(c < 0.5)
			weights[i] = 0;
		else weights[i] = c;
	}
	float error = 0.0, price, w0Correction, w1Correction, w2Correction;
	int iteration = 1;
	while(iteration < 100000){
		error = 0;
		for(int i = 0; i < nTraining; ++i)	{
			price = w0 + w1 * trainingData[i].area + w2 * trainingData[i].noOfRooms;
			error += (pow(trainingData[i].price - price, 2) * weights[i]) ;
			
			w0Correction += (trainingData[i].price - price) * weights[i];
			w1Correction += (trainingData[i].price - price) * trainingData[i].area * weights[i];
			w2Correction += (trainingData[i].price - price) * trainingData[i].noOfRooms * weights[i];
		}
		error /= (nTraining * 2);
		cout<<"Iteration "<<iteration++<<endl;
		if(error < desiredError)
			break;
				
		w0 += learningRate * w0Correction;
		w1 += learningRate * w1Correction;
		w2 += learningRate * w2Correction;
		cout<<"Weights : \n"<<w0<<"\t"<<w1<<"\t"<<w2<<endl;
	}
	testData.price = w0 + w1 * testData.area + testData.noOfRooms;
	cout<<"Test data :  \n"
		<<"Area = "<<testData.area
		<<"\nNo. of rooms : "<<testData.noOfRooms
		<<"\n\nPredicted price = "<<testData.price;
	return 0;
}
