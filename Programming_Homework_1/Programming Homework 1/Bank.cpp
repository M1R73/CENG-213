#include "Bank.h"

EventResult::EventResult(EventType type, int customerId, int bankerOrOfficerId, int timePoint)
    : type(type)
    , customerId(customerId)
    , bankerOrOfficerId(bankerOrOfficerId)
    , timePoint(timePoint)
{}

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    switch(r.type)
    {
        case ARRIVAL:
            s << "Customer(" << r.customerId
              << ") arrived at the bank." << std::endl;
            break;
        case QUEUE_ENTERED:
            s << "Customer(" << r.customerId
              << ") entered the queue at position " << r.bankerOrOfficerId << "." << std::endl;
            break;
        case QUEUE_EXITED:
            s << "Customer(" << r.customerId
              << ") exited the queue and was dispatched by Officer("
              << r.bankerOrOfficerId << ")." << std::endl;
            break;
        case SERVICE_STARTED:
            s << "Banker(" << r.bankerOrOfficerId
              << ") started serving Customer(" << r.customerId << ")." << std::endl;
            break;
        case SERVICE_COMPLETED:
            s << "Service for Customer(" << r.customerId
              << ") by Banker(" << r.bankerOrOfficerId
              << ") is completed." << std::endl;
            break;
        case INVALID_EVENT:
            s << "Invalid Event!" << std::endl;
            break;
        case FINISHED:
            s << "Simulation has finished." << std::endl;
            break;
    }

    return s;
}

Bank::Bank(int numBankers,
           const int* bankerServiceTimes,
           int numSecurityOfficers,
           const int* officerDispatchTimes,
           int bankersStartTime)
    : waitingQueue(numSecurityOfficers)
    , numberOfBankers(numBankers)
    , numberOfSecurityOfficers(numSecurityOfficers)
    , currentTime(0)
    , startTime(bankersStartTime)
{
    bankers = new Banker[numberOfBankers];
    for (int i = 0; i < numberOfBankers; ++i) {
        bankers[i] = Banker(i, bankerServiceTimes[i]);
        eventQueue.InsertItem(Event(currentTime + startTime, SERVICE_STARTED, Customer(), i));
    }

    securityOfficers = new SecurityOfficer[numberOfSecurityOfficers];
    for (int i = 0; i < numberOfSecurityOfficers; ++i) {
        securityOfficers[i] = SecurityOfficer(i, officerDispatchTimes[i]);
    }

}

Bank::~Bank()
{
    // TODO: Implement
}

void Bank::AddCustomer(int id, int priority)
{
    // TODO: Implement
}

EventResult Bank::DoSingleEventIteration()
{
    // TODO: Implement
    return EventResult();
}

std::ostream& operator<<(std::ostream& stream, const Bank& b)
{
    stream << "Bank State at Time " << b.currentTime << ":\n";
    stream << "Waiting Queue:\n" << b.waitingQueue << "\n";
    stream << "Service Queue:" << b.serviceQueue << "\n";
    stream << "Event Queue:" << b.eventQueue << "\n";
    return stream;
}