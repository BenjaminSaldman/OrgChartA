#pragma once
#include <vector>
#include <string>
#include <queue>
#include <stack>
const int BFS_SC=0;
const int REV_BFS=1;
const int ORD=2;
namespace ariel{
     class OrgChart{

        public:
            
            OrgChart(){root=nullptr;}
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
           
           

        
        private:
            struct Node{
                string val;
                vector<Node*>childs;
                Node(string data):val(data){} 

            };
            
            Node* root;
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
                        if(root) // If the root isn't a null pointer we starting the scan, else the graph isn't exist.
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
                        if(root)
                        {
                            q.push(root);
                        }
                         while(!q.empty())
                        {
                            size_t len=q.size();
                            for(unsigned i=0;i<len;i++)
                            {
                                Node* n=q.front();
                                order.push_back(n);
                                q.pop();
                                // Here the condition changed: we push from the right to the left.
                                for(int j=n->childs.size()-1;j>=0;j--)
                                {
                                    q.push(n->childs.at((unsigned)j));
                                }
                            }
                        }
                        // order now contains right to left BFS scan, we want to change the direction to 
                        // get reverse level order scan so we create a temp vector and replace the order vector.
                        vector<Node*>rev;
                        for(int i=order.size()-1;i>=0;i--)
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
                      
                        if(root)
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
                            for(int i=curr->childs.size()-1;i>=0;i--)
                            {
                                 st.push(curr->childs.at((unsigned)i));
                                
                            }
                        }
                       
            

                    }
               
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
                                BFS(root);
                            }
                        }
                        curr_num=0;
                    }
                    string& operator*()
                    {
                        return order[curr_num]->val;
                    }
                    string* operator->()
                    {
                         return &order[curr_num]->val;
                    }
                    iterator& operator++()
                    {
                        curr_num++;
                        if(curr_num>=order.size())
                        {
                            order.clear();
                        }
                        return *this;
                    }
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
                    bool operator==(const iterator& other)
                    {
                       if(order.size()!=0 && other.order.size()!=0)
                       {
                           return order[curr_num]==other.order[other.curr_num];
                       }
                       else{
                        return order.size()==0 && other.order.size()==0;
                       }
                    }
                    bool operator!=(const iterator& other)
                    {
                        return !(*this == other);
                    }



            };
            iterator begin()
            {
                return iterator(root,BFS_SC);
            }
            iterator end()
            {
                return iterator(nullptr,BFS_SC);
            }
            iterator begin_level_order()
            {
                return iterator(root,BFS_SC);
            }
            iterator end_level_order()
            {
                return iterator(nullptr,BFS_SC);
            }
            iterator begin_reverse_order()
            {
                return iterator(root,REV_BFS);
            }
            iterator reverse_order()
            {
                return iterator(nullptr,REV_BFS);
            }
            iterator begin_preorder()
            {
                return iterator(root,ORD);
            }
            iterator end_preorder()
            {
                return iterator(nullptr,ORD);
            }
            Node* findNode(Node* root ,const string& father)
            {
                queue<Node*>q;
                Node* ans=nullptr;
                bool temp=true;
                if(root)
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
             OrgChart& add_sub(const string& father, const string& son)
            {
                Node* n= findNode(root,father);
                if(n==nullptr)
                {
                    throw invalid_argument{"Node isn't exist!"};
                }
                Node* to_push=new Node(son);
                n->childs.push_back(to_push);
                return *this;
            }

        friend std::ostream& operator<<(ostream& output,const OrgChart& org){

            queue<Node*>q;
            Node* root=org.root;
            if(root)
            {
                q.push(root);
            }
            while(!q.empty())
            {
                size_t len=q.size();
                for(unsigned i=0;i<len;i++)
                {
                    Node* n=q.front();
                    output<<n->val<<endl; 
                    q.pop();
                    for(size_t j=0;j<n->childs.size();j++)
                    {
                        q.push(n->childs.at(j));
                    }
                }
            }
            return output;
        }
      

    };

};