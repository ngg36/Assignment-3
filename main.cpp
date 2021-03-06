#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Bakery {

    int id;
    string name;
    int quantity;
    double price;

};

// Rubric required function constructors. DO NOT EDIT.
void readBakery(ifstream& in,Bakery **bakeries, int N, int M);
void displayMenu();
void displayBakeryItems(Bakery **bakeries, int N, int M);
void displayHeader();
int searchMax(Bakery** bakeries, int N, int M);

void linearSearchandUpdate(Bakery* bakeries, string productName, int M);



void sortById(Bakery *bakeries, const int SIZE);
void sortByQuantityPrice(Bakery *bakeries, const int SIZE);
void displayBakery(const Bakery& bakery);
void releaseMemory(Bakery**, int, int);
Bakery** allocateMemory(int N, int M);





// custom constructors
void readBakeryMetadata(ifstream& in, int &numBakeries, int &numItems);

int main() {

    ifstream in;
    in.open("bakery.txt");

    int userInput = 0, result;
    int numBakeries = 0, numItems = 0;

    readBakeryMetadata(in, numBakeries, numItems);

    Bakery** arr = allocateMemory(numBakeries, numItems);

    readBakery(in, arr, numBakeries, numItems);
    
    displayBakeryItems(arr, numBakeries, numItems);
    
    while (userInput != 5) {

        
        displayMenu();

        cin >> userInput;

        switch (userInput) {
            case 1:
                displayBakeryItems(arr, numBakeries, numItems);
                break;

            case 2:
                
                for (int i = 0; i < numBakeries; i++) {
                    sortByQuantityPrice(arr[i], numItems);
                }

                break;
            case 3:

                result = searchMax(arr, numBakeries, numItems);
                break;
            
            case 4:
            {
                int num;
                string productName;
                cout << "Enter bakery ID:";
                cin >> num;
                cin.ignore();
                cout << endl << "Enter product name:";
                getline(cin, productName);
                linearSearchandUpdate(arr[num-1], productName, numItems);
          
                displayBakeryItems(arr, numBakeries, numItems);
            }
                break;

            case 5:
                break;
        }

    }

    releaseMemory(arr, numBakeries, numItems);



}


void linearSearchandUpdate(Bakery* bakeries, string productName, int M){
  for (int i = 0; i < M; i++){
    if(productName == bakeries[i].name){
      if(bakeries[i].quantity - 1 >= 0){
        bakeries[i].quantity = bakeries[i].quantity - 1;

        cout << endl <<"Successfully checked out " << productName << endl;
        break;

      }
      if (bakeries[i].quantity -1 < 0){
        cout << endl << "The item " << productName <<" does not exist" << endl;
        break;
      }
    }
    else
    {
      cout << endl << "The item " << productName <<" does not exist" << endl;
      break;
    }
  }
}

void displayHeader() {
    cout << left
         << setw(3) << "ID"
         << setw(26) << "Name"
         << setw(12) << "Quantity"
         << "Price"
         << endl;
}

int searchMax(Bakery** bakeries, int N, int M) {

    int maxN = 0, maxM = 0;

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < M; j++) {

            if (bakeries[i][j].quantity > bakeries[maxN][maxM].quantity) {

                maxN = i;
                maxM = j;

            }
        
        }

    }

    cout << "Product needs attention: " << bakeries[maxN][maxM].name << " " << bakeries[maxN][maxM].quantity << " in bakery " << N << endl;

    return 0;
}



void displayMenu(){
    cout << "\nMenu\n"
         << "1. Display bakeries sorted by id\n"
         << "2. Display bakeries sorted by quantity, then price-per-item\n"
         << "3. Find the product with maximum quantity among all bakeries\n"
         << "4. Purchase items\n"
         << "5. Quit the Program\n"
         << "Enter your choice:\n";
}

void readBakery(ifstream& in,Bakery **bakeries, int numBakeries, int numItems) {

    int currentBakery = 0, currentItem = 0;
    string blankline;

    while(getline(in,blankline)) {

        if(!blankline.size());
        else {
            bakeries[currentBakery][currentItem].id = stoi(blankline);
            getline(in, bakeries[currentBakery][currentItem].name);
            in >> bakeries[currentBakery][currentItem].quantity;
            in >> bakeries[currentBakery][currentItem].price;

            currentItem++;
        }

        if (currentItem == numItems) {
            currentItem = 0;
            currentBakery++;
        }

    }


}

void readBakeryMetadata(ifstream& in, int &numBakeries, int &numItems) {

    string blankline;

    in >> numBakeries;
    in >> numItems;

    return;
}

Bakery** allocateMemory(int N, int M) {

    Bakery** arr = new Bakery*[N]; //1st dimension

	for(int i = 0; i<N ; i++){
		arr[i] = new Bakery[M];
	}

    return arr;

}

void releaseMemory(Bakery** arr, int N, int M) {

    for(int i = 0; i < N; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}

void sortByQuantityPrice(Bakery *bakeries, const int SIZE) {

    for (int i = 0; i < SIZE - 1; i++) {

        if (bakeries[i].quantity > bakeries[i + 1].quantity) {

            swap(bakeries[i], bakeries[i + 1]);

        }

        if (bakeries[i].quantity == bakeries[i + 1].quantity) {
            
            if (bakeries[i].price < bakeries[i + 1].price) {

                swap(bakeries[i], bakeries[i + 1]);
    
            }
        }

    }


}

void displayBakery(const Bakery& bakery){
    cout << left
         << setw(3) << bakery.id
         << setw(26) << bakery.name
         << setw(12) << bakery.quantity
         << fixed << setprecision(1) << bakery.price
         << endl;
}

void displayBakeryItems(Bakery** bakeries, int N, int M) {

    displayHeader();

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < M; j++) {

            displayBakery(bakeries[i][j]);

        }

        cout << "--------" << endl;
    }
}