#include <iostream>
#include <fstream>
#include <string>

#include <sstream>  //sstream
using std::istringstream;

using namespace std;


///1- The FloatArray class stores a dynamic array of floats and its size.
class FloatArray
{
protected:
    float *arr;  //data Array
    int SizeOfArray;
public:
    //Default constructor
    FloatArray()
    {
        SizeOfArray=0;
        arr=NULL;
    }


    //A parameterized constructor that takes the array size.
    FloatArray(int s)
    {
        SizeOfArray=s;
        arr=new float[SizeOfArray];
    }




    //An add method that adds a float at the end of the array.
    virtual void Add(float X) //X refer to value
    {
        if (SizeOfArray!=0)
        {
            SizeOfArray++;
            float *saved = new float[SizeOfArray];
            for (int i=0;i<SizeOfArray-1;i++)
            {
                saved[i]=arr[i];
            }
            saved[SizeOfArray-1] = X;
            delete [] arr;
            arr = saved;
        }else
        {
            SizeOfArray++;
            arr=new float[SizeOfArray];
            arr[0] = X;
        }


    }


    float Get_Index(int i)
    {

        return arr[i];
    }


    /*Overloading for the extraction operator >> to read the array
    elements from the file (ifstream) and add them to the array.*/
    friend ifstream &operator >>(ifstream &is,const FloatArray &obj)
    {
        for(int i=0;i<obj.SizeOfArray;i++)
        {
            is>>obj.arr[i];
        }

        return is;
    }



    // Overloading for the insertion operator << to write the array to a file (ofstream)
    friend ofstream &operator <<(ofstream &os,const FloatArray &obj)
    {
        os<<obj.SizeOfArray<<"| "<<"\t";

        for(int i=0;i<obj.SizeOfArray;i++)
        {
            os<<obj.arr[i]<<"\t";
        }
        os<<endl;
        return os;
    }






    //friend stringstream &operator >>(stringstream &is,FloatArray &obj);


    //A destructor to deallocate the array
    ~FloatArray()
    {
        if(arr!=NULL)
        {
            delete []arr;
        }
    }

};



/// The SortedArray inherits from FloatArray  add method that adds a float at the right place in the array such that the array remains sorted with every addition.
class SortedArray : public FloatArray
{
    public:

        //Default constructor
        SortedArray():FloatArray()
        {

        }


        //A parameterized constructor
        SortedArray(int num): FloatArray(num)
        {

        }




        /* An add method that adds a float at the right place in the array
        such that the array remains sorted with every add. Don’t add to
        the array then sort but rather add in the right place.*/
        virtual  void Add(float X)
        {
            if(SizeOfArray==0)
            {
                FloatArray::Add(X);
            }
            else
            {
                int i=0;
                while(i<SizeOfArray && arr[i]<X)
                {
                    i++;
                }
                if(i==SizeOfArray)
                {
                    FloatArray::Add(X);
                }else
                {
                    FloatArray::Add(X);
                    for(int z=SizeOfArray - 2;z>=i;z--)
                    {
                        arr[z+1]=arr[z];
                    }
                    arr[i]=X;
                }
            }
        }





        //Destructor
        ~SortedArray(){}

};


/// The FrontArray inherits from FloatArray.
class FrontArray : public FloatArray
{
public:
    //Default constructor
    FrontArray():FloatArray()
    {

    }



    //A parameterized constructor
    FrontArray(int num): FloatArray(num)
    {

    }



    //An add method that adds a float at the front of the array.
    virtual void Add(float X)
    {
        if(SizeOfArray==0)
        {
            FloatArray::Add(X);
        }
        else
        {
            FloatArray::Add(X);
            for(int i =SizeOfArray-2;i>=0;i--)
            {
                arr[i+1]=arr[i];
            }
            arr[0]=X;
        }
    }


    //Destructor
    ~FrontArray(){}

};

// The PositiveArray that inherits from SortedArray.
class PositiveArray : public SortedArray
{
public:
    //Default constructor
    PositiveArray():SortedArray()
    {

    }



    //A parameterized constructor
    PositiveArray(int num):SortedArray(num)
    {

    }



    //An add method that adds a float to the array only if it’s a positive number. It then uses the add method of SortedArray.
    virtual void Add(float X)
    {
        if(X>0)
        {
            SortedArray::Add(X);
        }
    }



    //Destructor
    ~PositiveArray(){}

};


// The NegativeArray that inherits from SortedArray
class NegativeArray : public SortedArray
{
public:

    //Default constructor
    NegativeArray():SortedArray()
    {

    }


    //A parameterized constructor
    NegativeArray(int num):SortedArray(num)
    {

    }



    //An add method that adds a float to the array only if it’s a negative number. It then uses the add method of SortedArray.
    virtual void Add(float X)
    {
        if(X<0)
        {
            SortedArray::Add(X);
        }
    }

    //Destructor
    ~NegativeArray(){}

};
int main()
{
    string typeOfArray,line;
    int Size;
    string NameOfTheInputFile,NameOfTheOutputFile;


    cout<<"Enter The Name of the input file: ";
    cin>>NameOfTheInputFile;

    cout<<"Enter The Name of the output file: ";
    cin>>NameOfTheOutputFile;


    ifstream fileIn(NameOfTheInputFile);

    ofstream fileout(NameOfTheOutputFile);


    //Reads from a text file multiple lines
    while(!fileIn.eof())
    {
        fileIn>>typeOfArray>>Size;
        FloatArray obj(Size);
        fileIn>>obj;

        if(typeOfArray=="Array")
        {
            fileout<<obj;
        }
        else if(typeOfArray=="Front")
        {
            FrontArray F;
            for(int i=0;i<Size;i++)
            {
                F.Add(obj.Get_Index(i));

            }
            fileout<<F;
        }
        else if(typeOfArray=="Sorted")
        {
            SortedArray S;
            for(int i=0;i<Size;i++)
            {
                S.Add(obj.Get_Index(i));

            }
            fileout<<S;

        }
        else if(typeOfArray=="Positive")
        {
            PositiveArray P;
            for(int i=0;i<Size;i++)
            {
                P.Add(obj.Get_Index(i));

            }
            fileout<<P;

        }
        else if(typeOfArray=="Negative")
        {
            NegativeArray N;
            for(int i=0;i<Size;i++)
            {
                N.Add(obj.Get_Index(i));

            }
            fileout<<N;

        }
        getline(fileIn,line);

    }
    fileIn.close();
    fileout.close();



    return 0;
}
