#ifndef RECCHECK
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helperFunc (const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, size_t currentDay, size_t currentOpening, vector<size_t>& shiftsUsed);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{

    // NOTES: need to recurse through 0 -> n-1 days. + within each day, there are slots 0->d-1 that need to be filled
    // for each recursive position, try each possible worker (index 0 -> k-1)
    // need to track how many shifts have been worked so far for each worker -> use array? -> vector easier
    
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    if (dailyNeed == 0 || maxShifts == 0) {
        return false;
    }
    // sched is a n-by-d matrix with the d worker IDs who are scheduled to work on each of the n days
    // creating vector with size being the amount of workers - all entries set to 0 to start
    vector<size_t> shiftsUsed(avail[0].size(), 0);

    // # of workers: avail[0].size()
    // # of days: avail.size()
    //  ^^^ avail is a n by k matrix. k workers availability over n day period

    // adds rows to schedule (# of days) bc will be accessing them later to add worker IDs. even tho empty this is necessary
    sched.resize(avail.size());
    return helperFunc(avail, dailyNeed, maxShifts, sched, 0, 0, shiftsUsed);

}

bool helperFunc (const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, size_t currentDay, size_t currentOpening, vector<size_t>& shiftsUsed) {
        size_t numdays = avail.size();
        size_t numworkers = avail[0].size();

        // base case: completed all days in the matrix 
        if (currentDay >= numdays) {
            return true;
        }
        // @ the max opening for the row and need to move to the next day 
        if (currentOpening >= dailyNeed) {
            return helperFunc(avail, dailyNeed, maxShifts, sched, currentDay+1, 0, shiftsUsed);
        }

        // looping through all workers bc need to figure out which ones are available for current day and shift
        for (size_t i = 0; i < numworkers; i++) {
            // check if worker is available, hasnt used up all shifts
            if (avail[currentDay][i] == true && shiftsUsed[i] < maxShifts) {
                // also check if worker has been scheduled for this day already
                bool scheduled = false;
                for (size_t j = 0; j< sched[currentDay].size(); j++) {
                    if (sched[currentDay][j] == i) {
                        scheduled = true;
                        break;
                    }
                }
                if (scheduled == false) {
                    // we are filling schedule n (days) by d (# of workers needed per day)
                    sched[currentDay].push_back(i);
                    shiftsUsed[i]++;
                    if (helperFunc(avail, dailyNeed, maxShifts, sched, currentDay, currentOpening+1, shiftsUsed) == true) {
                        return true;
                    } else {
                        // backtracking work
                        shiftsUsed[i]--;
                        sched[currentDay].pop_back();
                    }
                }
            }
            
        }
        // if made out entire for loop, that means no worker w availability was found
            return false;
    }

