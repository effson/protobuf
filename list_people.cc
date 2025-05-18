#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "addressbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

void ListPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); ++i) {
    const tutorial::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "Name: " << person.name() << endl;
    if (person.email() != "") {
      cout << "Email-address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); ++j) {
      const tutorial::Person::PhoneNumber& phone_number = person.phones(j);
      string type;
      switch (phone_number.type()) {
        case tutorial::Person::MOBILE:
          type = "Mobile";
          break;
        case tutorial::Person::HOME:
          type = "Home";
          break;
        case tutorial::Person::WORK:
          type = "Work";
          break;
        default:
          type = "Unknown";
      }
      cout << "Phone number (" << type << "): " << phone_number.number() << endl;
    }

    if (person.has_last_updated()) {
      cout << "Updated: " << TimeUtil::ToString(person.last_updated()) << endl;
    }
  }
}

int main(int argc, char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <addressbook_file>" << endl;
    return -1;
  }

  tutorial::AddressBook address_book;
  
  {
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cerr << argv[0] << ": " << argv[1] << ": File not found. Creating a new file." << endl;
      return -1;
    }
    if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }
  ListPeople(address_book);
  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}