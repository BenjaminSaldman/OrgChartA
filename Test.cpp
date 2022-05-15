#include "doctest.h"
#include "OrgChart.hpp"
#include "string"
using namespace ariel;
TEST_CASE("Given tree")
{
    OrgChart organization;

    organization.add_root("CEO")
      .add_sub("CEO", "CTO")         
      .add_sub("CEO", "CFO")        
      .add_sub("CEO", "COO")         
      .add_sub("CTO", "VP_SW") 
      .add_sub("COO", "VP_BI");
      std::vector<string> vec;
      for(auto it=organization.begin_level_order();it!=organization.end_level_order();++it)
      {
          vec.push_back(*it);
      }
      CHECK_EQ(vec.size(),6);
      CHECK_EQ(vec[0],"CEO");
      CHECK_EQ(vec[1],"CTO");
      CHECK_EQ(vec[2],"CFO");
      CHECK_EQ(vec[3],"COO");
      CHECK_EQ(vec[4],"VP_SW");   
      CHECK_EQ(vec[5],"VP_BI");
      vec.clear();
      for(auto it:organization)
      {
          vec.push_back(it);
      }
      CHECK_EQ(vec.size(),6);
      CHECK_EQ(vec[0],"CEO");
      CHECK_EQ(vec[1],"CTO");
      CHECK_EQ(vec[2],"CFO");
      CHECK_EQ(vec[3],"COO");
      CHECK_EQ(vec[4],"VP_SW");   
      CHECK_EQ(vec[5],"VP_BI");
      vec.clear();
      for(auto it=organization.begin_reverse_order();it!=organization.reverse_order();it++)
      {
          vec.push_back(*it);
      }
      CHECK_EQ(vec.size(),6);
      CHECK_EQ(vec[0],"VP_SW");
      CHECK_EQ(vec[1],"VP_BI");
      CHECK_EQ(vec[2],"CTO");
      CHECK_EQ(vec[3],"CFO");
      CHECK_EQ(vec[4],"COO");   
      CHECK_EQ(vec[5],"CEO");
      vec.clear();
      for(auto it=organization.begin_preorder();it!=organization.end_preorder();it++)
      {
          vec.push_back(*it);
      }
      CHECK_EQ(vec.size(),6);
      CHECK_EQ(vec[0],"CEO");
      CHECK_EQ(vec[1],"CTO");
      CHECK_EQ(vec[2],"VP_SW");
      CHECK_EQ(vec[3],"CFO");
      CHECK_EQ(vec[4],"COO");   
      CHECK_EQ(vec[5],"VP_BI");
}
TEST_CASE("BAD CASES")
{
    OrgChart o;

    for(int i=0;i<10;i++)
    {
        CHECK_THROWS(o.add_sub("SUPER","FAIL"));
    }
    o.add_root("Parent");
    for(int i=0;i<10;i++)
    {
        CHECK_THROWS(o.add_sub("NOT_EXIST","fail"));
    }
}