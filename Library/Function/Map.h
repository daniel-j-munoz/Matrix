#include <iostream> 
#include <string>

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

        
        // set can be confused w/ set element?....
        // finds unique domain elements .....i believe so...
        // cal unique?..
        // unique_domain?...

        // call merge instead?...
        static Map<Domain, Codomain> merge(Map a, Map b){
            Map<Domain, Codomain> map;

            for(int i = 0; i < a.size(); i++){
                if(!map.contains(a.domain[i])){
                    map.add(a.domain[i], a.codomain[i]);
                }
            }

            for(int i = 0; i < b.size(); i++){
                if(!map.contains(b.domain[i])){
                    map.add(b.domain[i], b.codomain[i]);
                }
            }

            map.enumerate();

            return map;
        }






        // domain_contains
        // codomain_contains?....

        bool contains(Domain element){
            for(Domain thing : domain){
                if(element == thing){
                    return true; 
                }
            }
            return false;
        }        

        // merge domains? ... merge codomains?...
        // merge?... add??....
        // merge domains by default?..... idk.... to avoid repeating codomains?.... idk?....
        // what if merge requries that domain & codomain be unqiue?.....
        // so it requries that unqieu domain codomain pair?....
        
        // merges two maps. void or copy?...
        // does not repeat things...?...
        void merge(Map<Domain, Codomain> map){
            for(int i = 0; i < map.domain.size(); i++){
                if(!contains(map.domain[i])){
                    add(map.domain[i], map.codomain[i]);
                }
            }
            enumerate();
        }

        void enumerate(){
            for(int i = 0; i < size(); i++){
                codomain[i] = i;
            }
        }

        void sort_domain();
        void sort_codomain(); 


        void print(){
            for(int i = 0; i < size(); i++){
                cout << domain_at(i) << " ";
                cout << codomain_at(i) << "\n";
            }
            cout << "\n";
        }





        //.                    includes only...
        // merge                unique domain codomain pair
        // merge_domains        unique domain
        // merge_codomains       unique codmain
        // idk..............
        // maybe doesnt ahave to be unique idk.....
};



// pre image could return vector of preimages?...
// image could return vector of images?.... multiple mappings??...
// idk... woryy about that later.... fine for right now...
// just wory about it later..... just writing what comes to ehad...
// another class that handles non uneique mappings?.... idkk.... wory about it later....