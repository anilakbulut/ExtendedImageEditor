/*ANIL AKBULUT 151044029 PA3*/
/*Libraries I use in my code*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class IMAGE
{
private:
	int *imageArray; /*for dynamic array implement*/
	string format;/*stores the format of the file read*/
	int row,column,max;/*variables that store the row, column, and maximum number of pixels in the file.*/  
public:
	IMAGE(); /*constructor*/
	~IMAGE(); /*destructor */
	friend IMAGE operator+(const IMAGE& lhs,const IMAGE& rhs); /* + operator overload*/

	int read_image(); /*file read*/
	void write_image(); /*file write*/
	void Scripts(); /*script on my images*/
};

IMAGE::IMAGE(){
		imageArray = 0;
		format = "";
		row =0 ;
		column =0;
		max =0;	
}
IMAGE::~IMAGE(){
	delete[] imageArray; /*deallocated memory*/
	imageArray = 0;
}
IMAGE operator+(const IMAGE& lhs,const IMAGE& rhs){
	int i;
	const int one_pixel_digit = 3;
	IMAGE result; /*new object created and filled*/
	result.row = rhs.row;
	result.column = rhs.column;
	result.max = rhs.max;
	result.format = rhs.format;
	/*Memory allocated*/
	result.imageArray = new int[result.row * result.column * one_pixel_digit]; 

	for(i=0;i<result.row * result.column * one_pixel_digit;i++){
		result.imageArray[i] = lhs.imageArray[i] + rhs.imageArray[i];
	}
	for(i=0;i<result.row*result.column*one_pixel_digit;i++) { /*if elements of array > max number */
		if(result.imageArray[i] > result.max) result.imageArray[i] = result.max;
	}
	return result; /*return new object*/
}

int IMAGE::read_image(){ /*This function reads the necessary information for the class object from the file.*/
	const int one_pixel_digit = 3;
	string input_filename;
	cin >> input_filename;
	int i; /*use loops*/

	ifstream file(input_filename);
	
	if(file.is_open()){
		getline(file,format); /*first line stores file format*/
		file >> row >> column >> max; /*Stores the number of rows of columns and maximum pixels in the file*/
		imageArray = new int[row*column*one_pixel_digit];
		for(i=0;i<row*column*one_pixel_digit;i++) file >> imageArray[i];
		file.close();
		return 1;
	}else return 0;	/*error message*/
}
void IMAGE::write_image(){/*It is the function of writing the pixel values ​​to the file.*/
	string input_filename; /*it stores the file name that the user wants to write.*/
	cin >> input_filename;
	int i,j;/*variables for loops*/
	int k=0;
	ofstream file(input_filename); /*file writing process*/

	if(file.is_open()){ /*if file is open,continue*/
		/*write the row,column and max variables of the file.*/
		file << format << endl; 
		file << row << " " << column << endl;
		file << max << endl;
		/*write the pixel variables of the file.*/
		for(i=0;i<row;i++){ 
			for(j=0;j<column*3;j++){
				file << imageArray[k];
				k++;
				if(j+1 != column*3) file << " " ;
			}
			if( i + 1 != row ) file << endl;
		}
		file.close();/*file is closed*/
	}
}
void IMAGE::Scripts(){
	const int one_pixel_digit = 3; /*1 pixel equals o 3 digit*/
	float c_r,c_g,c_b; /*coefficient variables to be taken from the user */
	int i,j;/*variables for loops*/
	float count = 0; /*stores the sum of coefficient operations*/
	cin >> c_r ;
	cin >> c_g ;
	cin >> c_b ;
	/*If the coefficients are outside the specified limits, the program fails and closes.*/
	if(c_r>=1 || c_r < 0 || c_g>=1 || c_g < 0 || c_b>=1 || c_b < 0 ) return; 

	/*The required values ​​are collected and reassigned by reading the pixel values ​​three by three.*/
	for(i=0;i<row*column;i=i+3){
		count = imageArray[i]*c_r + imageArray[i+1]* c_g + imageArray[i+2]* c_b;
		if(count > max) count = max;
		imageArray[i]= count;
		imageArray[i+1]= count;
		imageArray[i+2]= count;
	}
}

int main()
{
	IMAGE *obj = new IMAGE[3]; /*dynamic object created*/

	int button=1,inner_button=1,tool_button=1; /*inner and outer's menu variables*/
	int order=0;
	int i=0;

	while(button!=0){ /*The program continues as long as the button is not 0.*/
		/*print on screen outer menu*/
		cout << "MAIN MENU" << endl;
		cout << "0 - Exit"  << endl;
		cout << "1 - Open An Image(D)" << endl;
		cout << "2 - Save Image Data(D)" << endl;
		cout << "3 - Scripts(D)" << endl;
		cin >> button;/*the loop wants from the user for the outer button value each time.*/		
		if(button == 1)
			while(inner_button!=0){
				cout << "OPEN AN IMAGE MENU" << endl;/*print on screen inner read menu*/
				cout << "0 - UP" << endl;
				cout << "1 - Enter The Name Of The Image File" << endl;
				cin >> inner_button; /*the loop wants from the user for the inner button value each time.*/
				if(inner_button == 1){
					if(obj[i].read_image()!=1) return 0;
					i++;
				}
			}
		else if(button == 2)
			while(inner_button!=0){
				cout << "SAVE IMAGE DATA MENU" << endl;
				cout << "0 - UP" << endl;
				cout << "1 - Choose Image and Enter A File Name(D)" << endl; /*print on screen inner save menu*/
				cin >> inner_button;/*the loop wants from the user for the inner button value each time.*/
				if(inner_button == 1){
					order = 0;
					while(order != 1 && order != 2 && order!=3){
						cout << endl;
						cout << "1 - First Image" << endl;
						cout << "2 - Second Image" << endl;
						cout << "3 - Third Image" << endl;
						cin >> order;
					}
					obj[order-1].write_image();
				}
			}
		else if(button == 3){
			while(tool_button!=0){
				cout << endl;
				cout << "0 - UP"<< endl;
				cout << "1 - GRAYSCALE MENU" << endl;
				cout << "2 - ADDITION"<< endl;
				cin >> tool_button;

				if(tool_button==1){
					while(inner_button!=0){ /*GRAYSCALE MENU*/
						cout << "CONVERT TO GRAYSCALE MENU" << endl;
						cout << "0 - UP" << endl;
						cout << "1 - Choose Image and Enter Coefficients For RED GREEN And BLUE Channels(D)" << endl; /*print on screen inner script menu*/
						cin >> inner_button;/*the loop wants from the user for the inner button value each time.*/
						if(inner_button == 1){
							order = 0;
							while(order != 1 && order != 2 && order!=3){
								cout << endl;
								cout << "1 - First Image" << endl;
								cout << "2 - Second Image" << endl;
								cout << "3 - Third Image" << endl;
								cin >> order;
							}
							obj[order-1].Scripts();
						}
					}
					inner_button=1;
				}
				if(tool_button==2)	obj[2] = obj[0] + obj[1] ; /*ADDITION MENU*/
			}
			tool_button=1;
		}
		inner_button=1; /*inner button update*/
	}
	delete []obj; /*deallocated memory*/
	return 1;
}