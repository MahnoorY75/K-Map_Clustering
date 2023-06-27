#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <sstream>
#include<time.h>
using namespace std;

struct Data_sets //Structure for the records
{
    //Records
    string id;
    double x;
    double y;
    int centorid_id; //Between 1 and 5
};

struct Centroid //Structure for the centroids
{
    double x; //x-axis
    double y; //y-axis
    double c_dis;
};

void Func(Data_sets& obj1, Centroid* obj2)
{

    for (int c = 0; c < 5; c++)
    {
        //Randomly generating the x and y axis for the centroids 

        obj2[c].c_dis = sqrt(((obj2[c].x - obj1.x) * (obj2[c].x - obj1.x)) + ((obj2[c].y - obj1.y) * (obj2[c].y - obj1.y)));
    }

    double min = 100;
    int cent_no = 0;
    for (int j = 0; j < 5; j++)
    {
        if (obj2[j].c_dis < min) //Finding the minimum distance so that to get the index number
        {
            min = obj2[j].c_dis;
            cent_no = j + 1; //Stores the index number
        }
    }
    obj1.centorid_id = cent_no;
}

int main()
{

    string line, word; //Variables for csv file reading
    int rows = 4000; //No of rows of the file
    int columns = 3; //No of coloumns of the file
    string** Data = new string* [rows]; //2D dynamic array to store the data
    for (int i = 0; i < rows; i++)
    {
        Data[i] = new string[columns]; //Dynamic Allocation
    }
    vector<vector<string>> content;
    vector<string> row;
    string fname = "driver-data.csv"; //File to read 
    fstream file(fname, ios::in);

    int i = 0; //Row counter
    int j = 0; //Coloumn counter
    if (file.is_open())
    {
        while (getline(file, line))
        {
            j = 0;
            row.clear();

            stringstream str(line);

            while (getline(str, word, ',')) //Reading values separated with comma in the csv file
            {
               
               
                   Data[i][j] = word; //Storing values in the dnamic array
                 
                   j++;
                
            }

            row.push_back(word);
            content.push_back(row);
            i++;
            if (i == 4000)
            {
                break;
        }
        }
      
    }
    file.close();

    //Creating the 4000 Structure Array for File data
    Data_sets Data_objs[4000];
    for (int j = 0; j < 4000; j++)
    {
        Data_objs[j].id = "  3.42331e+09";
        Data_objs[j].x = stod( Data[j][1]);
        Data_objs[j].y = stod(Data[j][2]);
    }
  /*  for (int j = 0; j < 4000; j++)
    {
        cout << Data_objs[j].id<<"  ";
       cout << Data_objs[j].x<<"  ";
       cout << Data_objs[j].y<<"  ";
       cout << endl;
    }*/

    //Finding max in the x coloumn
    double max1 = 0;
    for (int k = 0; k < 4000; k++)
    {
        if (Data_objs[k].x > max1)
        {
            max1 = Data_objs[k].x;
        }
    }
    //Finding max in the y coloumn
    double max2 = 0;
    for (int l = 0; l < 4000; l++)
    {
        if (Data_objs[l].y > max2)
        {
            max2 = Data_objs[l].y;
        }
    }
    //Dividing each value of x col with max1 and y col of max2
    //Updating the Data_obj structure
    for (int k = 0; k < 4000; k++)
    {
        Data_objs[k].x = (Data_objs[k].x / max1);
        Data_objs[k].y = (Data_objs[k].y / max2);
    }
    //Centroid structure object
    Centroid centroid[5]; //Taking 5 centroids

    srand((unsigned)time(NULL));
    for (int k = 0; k < 5; k++)
    {
        centroid[k].x = (double)(rand() % 10) + 1;
        centroid[k].y = (double)(rand() %  10) + 1;
        centroid[k].x = centroid[k].x / 10;
        centroid[k].y = centroid[k].y / 10;

    }
    bool flag = true;

    do
    {
        flag = true;
        for (int j = 0; j < 4000; j++)
        {
            Func(Data_objs[j], centroid);
        }
        //cout << Data_objs[5].centorid_id;
     /*   for (int k = 0; k < 4000; k++)
        {
            cout << Data_objs[k].centorid_id<<endl;
       }*/
        double sum_x = 0.0;
        double sum_y = 0.0;
        int count = 0;
        double mean_x = 0.0;
        double mean_y = 0.0;
        for (int k = 0; k < 5; k++) //Counter 1 to compare 5 centroids id with each row of records
        {
            sum_x = 0.0;
            sum_y = 0.0;
            count = 0;
            for (int j = 0; j < 4000; j++) //Counter 2 to compare each record with sepcific centroid id
            {
                if (Data_objs[j].centorid_id == k + 1)
                {
                    count++; //Stores number of records with specific index
                    //Adding each record's x and y axis
                    sum_x = sum_x + Data_objs[j].x;
                    sum_y = sum_y + Data_objs[j].y;
                }
            }

            //Calclating average
            mean_x = (sum_x / count);
            mean_y = (sum_y / count);
            if (centroid[k].x != mean_x || centroid[k].y != mean_y)
                flag = false;
            //New x and y axis for centroids
            centroid[k].x = mean_x;

            centroid[k].y = mean_y;

        }
    } while (!flag);

  /*  for (int k = 0; k < 4000; k++)
    {
        cout << Data_objs[k].centorid_id << endl;
    }*/
   // Writing the Final Data records into the File.

    ofstream write;
    write.open("test.csv", ios_base::app);
    for (int i = 0; i < 4000; i++)
    {
        write << Data_objs[i].id << "," <<Data[i][1] << "," << Data[i][2] << "," << Data_objs[i].centorid_id << endl;

  }

    write.close();
    cout << "Data Records Written into the output.csv file succesfully :)" << endl;
    //Free each sub-array

    //for (int i = 0; i < 3; ++i) {
    //    delete[] Data[i];

    //}
    ////Free the array of pointers
    //delete[] Data;

    return 0;

}