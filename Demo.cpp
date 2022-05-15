/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */
/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
  OrgChart organization;
  organization.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO

  cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
       CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
 */

  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: CEO CTO CFO COO VP_SW VP_BI
  for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: VP_SW VP_BI CTO CFO COO CEO
  for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: CEO CTO VP_SW CFO COO VP_BI

  for (auto element : organization)
  { // this should work like level order
    cout << element << " " ;
  } // prints: CEO CTO CFO COO VP_SW VP_BI

  // demonstrate the arrow operator:
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << it->size() << " " ;
  } // prints: 3 3 3 3 5 5
}

// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <stdexcept>
// using namespace std;

// #include "OrgChart.hpp"
// using namespace ariel;

// int main() {
//   OrgChart organization;
//   string name;
//   organization.add_root("CEO")
//       .add_sub("CEO", "CTO")         
//       .add_sub("CEO", "CFO")         
//       .add_sub("CEO", "COO")        
//       .add_sub("CTO", "VP_SW") 
//       .add_sub("COO", "VP_BI");
//   int dummy=0;    
//   cout<<"Welcome to Ex5 Demonstration, now you will see the full org chart but first, please enter your name:"<<endl;
//   cin>>name;
//   cout<<"Hello "<<name<<" now the demo will start!"<<endl;
//   cout << organization << endl; 
//   cout<<"You now saw the org chart, let's see some scans on it: "<<endl;
//   cout<<"Enter any number to continue"<<endl;
//   cin>>dummy;
//   for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
//   {
//     cout << (*it) << " " ;
//   }
//   cout<<endl;
//   cout<<"The first scan is level order scan, we scan every level of the tree (from the root), it also called BFS scan."<<endl;
//   cout<<"Enter any number to continue"<<endl;
//   cin>>dummy;
//   for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
//   {
//     cout << (*it) << " " ;
//   } 
//   cout<<endl;
//   cout<<"The second scan is reverse level order scan, here we start the scan from the leaves to the root."<<endl;
//   cout<<"Enter any number to continue"<<endl;
//   cin>>dummy;
//   for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
//     cout << (*it) << " " ;
//   } 
//   cout<<endl;
//   cout<<"The last scan is preorder scan, we scan every left sub-tree of the org-chart here."<<endl; 
//   cout<<"Enter any number to continue"<<endl;
//   cin>>dummy;
//   cout<<"End of demo, Hope you enjoyed "<<name<<"."<<endl;
// }
