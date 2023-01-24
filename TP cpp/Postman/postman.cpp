#include <iostream> //Library for input and output
#include <string> // Library for string manipulation
#include <fstream> //Library for file manipulation
#include <sstream> //Library for string streams
#include <cstdlib> //Library for C-style data types
#include <cstring> //Library for C-style strings
#include <algorithm> //Library for algorithms
#include <cryptopp/aes.h> //Library for AES encryption
#include <cryptopp/filters.h> //Library for filters
#include <cryptopp/modes.h> //Library for modes

using namespace std;

//This class is used to store data related to a postman, letter or parcel
class Data {
private:
  string postman_name; //Postman's name
  string addressee; //Addressee of the letter/parcel
  string type; //Type of the letter/parcel

public:
  Data(string p, string a, string t) { //Constructor
    postman_name = p;
    addressee = a;
    type = t;
  }
  string getPostmanName() { //Function to get postman's name
    return postman_name;
  }
  string getAddressee() { //Function to get addressee
    return addressee;
  }
  string getType() { //Function to get type
    return type;
  }
};

//This class is used to store the data in the flat file
class DataFile {
private:
  string fileName; //Name of the file
  vector<Data> data; //Vector of data
  CryptoPP::SecByteBlock key; //Encryption key

public:
  DataFile(string f) { //Constructor
    fileName = f;
  }
  void readData() { //Function to read data from file
    ifstream inFile;
    inFile.open(fileName.c_str());
    if (!inFile) { //If file not found, throw an error
      cerr << "Unable to open file";
      exit(1);
    }
    string line;
    while (getline(inFile, line)) { //Read line by line
      stringstream ss(line);
      string postman_name, addressee, type;
      getline(ss, postman_name, ','); //Split the line by comma
      getline(ss, addressee, ',');
      getline(ss, type, ',');
      data.push_back(Data(postman_name, addressee, type)); //Push data into the vector
    }
    inFile.close(); //Close the file
  }
  void writeData() { //Function to write data to file
    ofstream outFile;
    outFile.open(fileName.c_str());
    for (int i = 0; i < data.size(); i++) { //Iterate through the vector
      outFile << data[i].getPostmanName() << ","
              << data[i].getAddressee() << ","
              << data[i].getType() << endl; //Write data to file
    }
    outFile.close(); //Close the file
  }
  void encryptData() { //Function to encrypt data
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, key);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(fileName));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(fileName.c_str()), fileName.length() + 1); //Encrypt the file
    stfEncryptor.MessageEnd();
  }
  void decryptData() { //Function to decrypt data
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, key);
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(fileName));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(fileName.c_str()), fileName.length() + 1); //Decrypt the file
    stfDecryptor.MessageEnd();
  }
};

int main() {
  DataFile df("data.txt");
  df.readData(); //Read the data
  df.writeData(); //Write the data
  df.encryptData(); //Encrypt the data
  df.decryptData(); //Decrypt the data
  return 0;
}
