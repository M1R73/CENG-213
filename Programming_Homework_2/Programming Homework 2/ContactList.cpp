#include "ContactList.h"
#include <iostream>

ContactList::ContactList() {}

ContactList::~ContactList() {}

void ContactList::addContact(const std::string &name, const ContactInfo &info) {
    contacts.put(name,info);
}

bool ContactList::deleteContact(const std::string &name) {
    return contacts.deletekey(name);
}

void ContactList::updateContact(const std::string &name, const ContactInfo &newInfo) {
    contacts.update(name,newInfo);
}



const ContactInfo &ContactList::getContact(const std::string &name) const {
    return contacts.get(name);
}



void ContactList::iterateAlphabetically()  {

}

