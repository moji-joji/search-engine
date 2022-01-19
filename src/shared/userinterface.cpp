// #include <stringutils.h>
// #include <trie.h>
// #include <userinterface.h>

// #include <iostream>
// using namespace std;

// void userInterface(Trie &trie)
// {
//     cout << "|||\t\tWelcome to Hashmap-uh!\t\t|||" << endl;
//     int choice;
//     while (1)
//     {
//         cout << "Enter -9999 to exit" << endl;
//         cout << "Enter 1 to search for a phrase" << endl;
//         cout << "Enter 2 to search for auto complete" << endl;
//         cout << "Enter 3 to search for an exact title" << endl;
//         cin >> choice;
//         cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
//         string inputQuery;
//         if (choice == -9999)
//             break;
//         switch (choice)
//         {
//         case 1:
// string userQuery;
//   userQuery.reserve(128);
//   cout << "Enter a query: ";
//   getline(cin, userQuery);

//   DoublyLinkedList<uint32_t> wordFileIds;
//   DoublyLinkedList<string> words;
//   // lexicon [word] -> wordId
//   // short description => wordFileIds = {1, 2}
//   getFileIdFromQuery(userQuery, wordFileIds, words, lexiconMap);

//   fetchResults(words, wordFileIds, metadata);


//             break;
//         case 2:
//             cout << "Enter a word: " << endl;
//             // cin.getline(inputQuery,str);
//             // cin.clear();

//             // cin >> inputQuery;
//             getline(cin,inputQuery);

//             cout << "Suggestions: " << endl;
//             trie.prefixSearch(trie.root, inputQuery);
//             break;
//         case 3:
//           cout << "Enter exact file title: ";
//             getline(cin,inputQuery);
//             int result = trie.search(inputQuery)

//             if (result > 0)
//             {
//                 cout << inputQuery << " Found " << result << ".txt" << endl;
//             }
//             else
//             {
//                 cout << inputQuery << " Not found!" << endl;
//             }
//             cin.clear();


//         default:
//             cout << "Invalid choice. Try again: " << endl;
//             break; 
//         }
//     }
// }
