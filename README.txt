Ramon Rovirosa & Shervin Shaikh

CS170 Project 1




-- Lottery Scheduler --
Our do_lottery function iterates over all the processes with a priority of 17 and add up all of their tickets.  We then use the random number generator to get a specific lottery number in that range.  In the second for loop, we once again iterate through all of the processees and decrement the luckyNumber until we get it below 0, stating that we've reached the process that holds the winning ticket.  Once we are there, we set the priority to 16 and run that process.