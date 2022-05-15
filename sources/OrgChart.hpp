#pragma once
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <iostream>

const int BFS_SC=0;
const int REV_BFS=1;
const int ORD=2;
using namespace std;
namespace ariel{
     class OrgChart{
        
        private:
       
        /**
         * @brief private node struct to represent n-tree -> tree with n childs.
         * 
         */
            struct Node{
                string val;
                vector<Node*>childs;
                Node(const string& data):val(data){} 

            };
        
            Node* root; // tree root.
        public:
            class iterator{
                private:
                    size_t curr_num;
                    vector<Node*> order;
                public:
                    /**
                     * @brief BFS scan (aka. level order scan)
                     * we are scanning every level of the tree.
                     * Based on: https://he.wikipedia.org/wiki/%D7%90%D7%9C%D7%92%D7%95%D7%A8%D7%99%D7%AA%D7%9D_%D7%97%D7%99%D7%A4%D7%95%D7%A9_%D7%9C%D7%A8%D7%95%D7%97%D7%91
                     * @param root 
                     */
                    void BFS(Node* root)
                    {
                        queue<Node*>q; // queue, in the BFS scan we use a queue to save the nodes of the graph.
                        if(root!=nullptr) // If the root isn't a null pointer we starting the scan, else the graph isn't exist.
                        {
                            q.push(root);
                        }
                        // We scan till we covered all the nodes.
                        while(!q.empty())
                        {
                            size_t len=q.size(); // The size of the current level.
                            for(unsigned i=0;i<len;i++)
                            {
                                Node* n=q.front(); // Get the first child node (or root).
                                order.push_back(n); // Push the node to the covered nodes.
                                q.pop(); // Remove the node from the queue, we already used it.
                                // Push the node's child to the queue.
                                for(size_t j=0;j<n->childs.size();j++)
                                {
                                    q.push(n->childs.at(j));
                                }
                            }
                        }
                    }
                    /**
                     * @brief a reverse BFS scan (aka. reverse level order).
                     * 
                     * @param root 
                     */
                    void reverse_BFS(Node* root)
                    {
                        queue<Node*>q;
                        if(root!=nullptr)
                        {
                            q.push(root);
                        }
                         while(!q.empty())
                        {
                            int len=q.size();
                            for(unsigned i=0;i<len;i++)
                            {
                                Node* n=q.front();
                                order.push_back(n);
                                q.pop();
                                // Here the condition changed: we push from the right to the left.
                                for(int j=(int)n->childs.size()-1;j>=0;j--)
                                {
                                    q.push(n->childs.at((unsigned)j));
                                }
                            }
                        }

                        // order now contains right to left BFS scan, we want to change the direction to 
                        // get reverse level order scan so we create a temp vector and replace the order vector.
                        vector<Node*>rev;
                        for(int i=(int)order.size()-1;i>=0;i--)
                        {
                            rev.push_back(order.at((unsigned)i));
                        }
                        for(int i=0;i<rev.size();i++)
                        {
                            order[(unsigned)i]=rev[(unsigned)i];
                        }
                        order=rev;
                    }
                    /**
                     * @brief preorder scan on graph -> father -> son -> grandson -> son -> grandson.
                     * based on: https://www.youtube.com/watch?v=elQcrJrfObg&ab_channel=TusharRoy-CodingMadeSimple
                     * @param root 
                     */
                    void preorder(Node* root)
                    {
                        stack<Node*>st; // Stack that holds the nodes we didn't add to the order.
                      
                        if(root!=nullptr)
                        {
                            st.push(root);
                        }
                        /**
                         * @brief while the stack isn't empty take the last nodes inserted to the 
                         * stack and push him to the order, than scan all his childs from the right to the left.
                         * This let us scan every left sub-tree to the end. 
                         */
                        while(!st.empty())
                        {
                            Node* curr=st.top();
                            st.pop();
                            order.push_back(curr);
                            for(int i=(int)curr->childs.size()-1;i>=0;i--)
                            {
                                 st.push(curr->childs.at((unsigned)i));
                                
                            }
                        }
                       
            

                    }
                /**
                 * @brief Construct a new iterator object
                 * 
                 * @param root 
                 * @param CODE // type of iterator- level-order, preorder or reverse level-order.
                 */
                    iterator(Node* root,const int CODE)
                    {
                        if(CODE==REV_BFS)
                        {
                            reverse_BFS(root);
                        }
                        else{
                            if(CODE==ORD)
                            {
                                preorder(root);
                            }
                            else{
                                BFS(root); // default order, used for level order and begin.
                            }
                        }
                        curr_num=0; // pointer to first element in the list.
                    }
                    /**
                     * @brief 
                     * 
                     * @return the next element.
                     */
                    string& operator*()
                    {
                        return order[curr_num]->val;
                    }
                     /**
                     * @brief 
                     * 
                     * @return the next element.
                     */
                    string* operator->()
                    {
                         return &order[curr_num]->val;
                    }
                    /**
                     * @brief 
                     * 
                     * @return iterator& uses for ++it.
                     */
                    iterator& operator++()
                    {
                        curr_num++;
                        if(curr_num>=order.size())
                        {
                            order.clear();
                        }
                        return *this;
                    }
                    /**
                     * @brief 
                     * 
                     * @return iterator& uses for it++.
                     */
                    iterator& operator++(int)
                    {
                        iterator temp=*this;
                        curr_num++;
                        if(curr_num>=order.size())
                        {
                            order.clear();
                        }
                        return *this;
                    }
                    /**
                     * @brief 
                     * There are two cases:
                     * both of the iterators are empty and than return true or
                     * the sizes/objects are diffrent and than return false.
                     * @param other 
                     * @return true 
                     * @return false 
                     */
                    bool operator==(const iterator& other)
                    {
                       if(!order.empty()&& !other.order.empty())
                       {
                           return order[curr_num]==other.order[other.curr_num];
                       }
                        size_t t1=order.size();
                        size_t t2=other.order.size();
                        return t1==0 && t2==0;
                    }
                    bool operator!=(const iterator& other)
                    {
                        return !(*this == other);
                    }



            };
            /**
             * @brief 
             * 
             * @return iterator used for forEach loop.
             */
            iterator begin()
            {
                return iterator(root,BFS_SC);
            }
            static iterator end()
            {
                return iterator(nullptr,BFS_SC);
            }
            iterator begin_level_order()
            {
                return iterator(root,BFS_SC);
            }
            static iterator end_level_order()
            {
                return iterator(nullptr,BFS_SC);
            }
            iterator begin_reverse_order()
            {
                return iterator(root,REV_BFS);
            }
            static iterator reverse_order()
            {
                return iterator(nullptr,REV_BFS);
            }
            iterator begin_preorder()
            {
                return iterator(root,ORD);
            }
            static iterator end_preorder()
            {
                return iterator(nullptr,ORD);
            }
   
            /**
             * @brief 
             * 
             * @param root 
             * @param father 
             * @return Node* that his value is father.
             */
            static Node* findNode(Node* root ,const string& father)
            {
                queue<Node*>q;
                Node* ans=nullptr;
                bool temp=true;
                if(root!=nullptr)
                {
                    q.push(root);
                }
                while(!q.empty()&&temp)
                {
                    size_t len=q.size();
                    for(unsigned i=0;i<len;i++)
                    {
                        Node* n=q.front();
                        if(n->val==father)
                        {
                            ans=n;
                            temp=false;
                            break;
                        }
                        q.pop();
                        for(size_t j=0;j<n->childs.size();j++)
                        {
                            q.push(n->childs.at(j));
                        }
                    }
                }
                return ans;
            }
          
  
            /**
             * @brief Construct a new Org Chart object used for make tidy...
             * 
             * @param other 
             */
            OrgChart(OrgChart& other)
            {
                if(other.root==nullptr)
                {
                    root=nullptr;
                }else{
                    root=new Node(other.root->val);
                    root->childs=other.root->childs;
                }
            }
            /**
             * @brief Construct a new Org Chart object used for make tidy...
             * 
             * @param other 
             */
            OrgChart& operator=(OrgChart other)
            {
                if(this==&other)
                {
                    return *this;
                }
                Node* temp=root;
                root=new Node(other.root->val);
                delete temp;
                return *this;
            }
            /**
             * @brief Construct a new Org Chart object used for make tidy...
             * 
             * @param other 
             */
            OrgChart& operator=(OrgChart &&other) noexcept
            {
                if(this==&other)
                {
                    return *this;
                }
                Node* temp=root;
                root=new Node(other.root->val);
                delete temp;
                return *this;
            }
            /**
             * @brief Construct a new Org Chart object used for make tidy...
             * 
             * @param other 
             */
            OrgChart(OrgChart && other) noexcept
            {
                root=other.root;
            }
            OrgChart(){root=nullptr;}
                      
            /**
             * @brief 
             * 
             * @param father 
             * @param son 
             * @return OrgChart& insert a node to an existing parent.
             * If the parent isn't exist, throw an exception.
             */
            OrgChart& add_sub(const string& father, const string& son)
            {
                if(root==nullptr)
                {
                    throw invalid_argument{"No root in the graph!"};
                }
                Node* n= findNode(root,father);
                
                if(n==nullptr){
                    throw invalid_argument{"can't find node."};
                    
                }
                Node* to_push=new Node(son);
                n->childs.push_back(to_push);
                return *this;
            }
            OrgChart& add_root(const string& val)
            {
                if(root==nullptr)
                {
                    root=new Node(val);
                }else{
                    root->val=val;
                }
                
                return *this;
            }
            ~OrgChart()
            {
                 queue<Node*>q; // queue, in the BFS scan we use a queue to save the nodes of the graph.
                 vector<Node*>order;
                 if(root!=nullptr) // If the root isn't a null pointer we starting the scan, else the graph isn't exist.
                  {
                    q.push(root);
                  }
                    // We scan till we covered all the nodes.
                while(!q.empty())
                {
                    size_t len=q.size(); // The size of the current level.
                    for(unsigned i=0;i<len;i++)
                    {
                        Node* n=q.front(); // Get the first child node (or root).
                        order.push_back(n); // Push the node to the covered nodes.
                        q.pop(); // Remove the node from the queue, we already used it.
                        // Push the node's child to the queue.
                        for(size_t j=0;j<n->childs.size();j++)
                        {
                            q.push(n->childs.at(j));
                        }
                    }
                }
                for(unsigned i=0;i<order.size();i++)
                {
                    delete order.at(i);
                }
            }

        friend std::ostream& operator<<(std::ostream& output,const OrgChart& org){

            queue<Node*>q;
            
            q.push(nullptr);
            q.pop();
            Node* root=org.root;
            if(root!=nullptr)
            {
                q.push(root);
            }
            while(!q.empty())
            {
                size_t len=q.size();
                for(unsigned i=0;i<len;i++)
                {
                    Node* n=q.front();
                    output<<n->val<<' '; 
                    q.pop();
                    for(size_t j=0;j<n->childs.size();j++)
                    {
                        q.push(n->childs.at(j));
                    }
                }
                output<<'\n';
            }
            return output;
        }
      

    };

};