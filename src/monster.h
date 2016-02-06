#ifndef _MONSTER_H
#define _MONSTER_H

//Mike Lukas -p2prog03-             - monster.h -
//Class definition for a monster.  This class holds all the attributes
//and operations a monster will need, such as HP changing and accessing
//various attributes of the monster from in the program

#include <string>

using std::string;

class Monster
    {
        private:
            int mHP;                //current hit points (life)
            int mmaxHP;         //maximum hit points
            int AP;             //attack power
            int DP;             //defense percentage
            int SP;             //speed points
            int expPoints;          //number of expPoints player gets 
                                    //from beating monster
            string monsterName;


        public:
            Monster();
            void SetAttributes(int, int, int, int, int, string&);
            void ChangeHP(int);
                    
            string ShowName() const;
            int Damage() const;
            int Defense() const;
            int mHealth() const;
            int mMaxHealth() const;
            int Speed() const;
            int Experience() const;
    };

#endif
