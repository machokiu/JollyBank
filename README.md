# JollyBank

Five classes are included in this assignment: Bank, Account, AccountTree, Fund, and Transaction.
The Bank class interacts with most of the other classes. It reads the input file and stores the basic account information, such as the first name, last name, and account ID, to the Account class. It also stores the operation (O, W, D, T, H) to the Transaction class.

The Account class stores the basic information of the account owner, such as the Account ID and the Fund ID. It would be ideal to have a fund array to store each owner's different funds. It is also helpful to have a print function to print the history of each fund (by calling the print history method from Fund) and each account (by calling the own print history method of the whole account). Additionally, it should provide an error message for non-successful transactions.

The Fund class is a helper class of the Account. Each fund can perform its separate process, and it has its own print history method.
