#include <iostream> 
#include <string>
#include <vector>

using namespace std; 

#pragma once

template <typename Domain, typename Codomain>
class Map {
    public: 
        vector<Domain> domain = {}; 
        vector<Codomain> codomain = {}; 


        // push back? name should indicate that it appends a pair
        void add(Domain a, Codomain b){
            domain.push_back(a); 
            codomain.push_back(b);
        }



        Codomain image(Domain element){
            int index = 0; 
            for(int i = 0; i < domain.size(); i++){
                if(element == domain[i]){
                    index = i; 
                    break; 
                }
            }
            return codomain[index];
        }

        Domain pre_image(Codomain element){
            int index = 0; 
            for(int i = 0; i < codomain.size(); i++){
                if(element == codomain[i]){
                    index = i; 
                    break; 
                }
            }

            return domain[index];
        }

        void set_image(Domain element, Codomain new_image){
            for(int i = 0; i < domain.size(); i++){
                if(element == domain[i]){
                    codomain[i] = new_image;
                    break; 
                }
            }
        }

        void set_pre_image(Codomain element, Domain new_pre_image){
            for(int i = 0; i < codomain.size(); i++){
                if(element == codomain[i]){
                    domain[i] = new_pre_image;
                    break; 
                }
            }
        }

        bool in_domain(Domain element){
            for(Domain x : domain){
                if(element == x){
                    return true; 
                }
            }
            return false;
        }

        bool in_codomain(Codomain element){
            for(Codomain x : codomain){
                if(element == x){
                    return true; 
                }
            }
            return false; 
        }

        Domain domain_at(int ith){
            return domain[ith]; 
        }

        Codomain codomain_at(int ith){
            return codomain[ith];
        }

        // int domain_index()

        int size(){
            return domain.size();
        }

        void empty(){
            domain = {}; 
            codomain = {};
        }


        bool contains(Domain element){
            for(Domain thing : domain){
                if(element == thing){
                    return true; 
                }
            }
            return false;
        }        

        void enumerate(){
            for(int i = 0; i < size(); i++){
                codomain[i] = i;
            }
        }


        void print(){
            for(int i = 0; i < size(); i++){
                cout << domain_at(i) << " ";
                cout << codomain_at(i) << "\n";
            }
            cout << "\n";
        }



        
};

