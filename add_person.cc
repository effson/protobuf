#include <ctime>
#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "addressbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

void PromptForAddress(tutorial::Person* person) {
  cout << "Enter person ID number: ";
  int id;
  cin >> id;
  person->set_id(id);
  cin.ignore(256, '\n'); // Ignore the newline character left in the input buffer

  cout << "Enter name: ";
  getline(cin, *person->mutable_name());

  cout << "Enter email address (blank for none): ";
  string email;
  getline(cin, email);
  person->set_email(email);
  while (true) {
    cout << "Enter a phone number (or leave blank to finish): ";
    string number;
    getline(cin, number);
    if (number.empty()) break;

    tutorial::Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number(number);
  

    cout << "Is this a mobile, home, or work phone? ";
    string phone_type;
    getline(cin, phone_type);
    if (phone_type == "mobile") {
      phone_number->set_type(tutorial::Person::MOBILE);
    } else if (phone_type == "home") {
      phone_number->set_type(tutorial::Person::HOME);
    } else if (phone_type == "work") {
      phone_number->set_type(tutorial::Person::WORK);
    } else {
      cout << "Unknown phone type. Using Default." << endl;
    }
  }
  *person->mutable_last_updated() = TimeUtil::SecondsToTimestamp(time(nullptr));
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage: "<< argv[0] << " <addressbook_file>" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cerr << argv[0] << ": " << argv[1] << ": File not found. Creating a new file." << endl;
        } else if (!address_book.ParseFromIstream(&input)) {
            cerr << argv[0] << ": " << argv[1] << ": Failed to parse address book." << endl;
            return -1;
        }
    }

    PromptForAddress(address_book.add_people());
    {
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << argv[0] << ": " << argv[1] << ": Failed to write address book." << endl;
            return -1;
        }
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}