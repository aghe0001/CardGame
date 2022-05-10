// TestNana.cpp : Defines the entry point for the application.
//

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include <time.h>


void clicked(int a) {
    std::cout << "i select card no: " << a << std::endl;
}

int main()
{
    using namespace nana;
    bool a = true;
    //Define my image variables
    paint::image front, card1, card2, card3, card4, card5, card6, card7, card8, card9, card10;
    int checkimage1=50, checkimage2=52;

    //including audio
    audio::player player("winner.wav");
    audio::player pyayerloos("lost.wav");
    audio::player playerwin("match.wav");
    threads::pool pool(1);

    //Define a form.
    form fm(API::make_center(550, 550));
    fm.caption(("My Final Project"));
    static place place(fm);
    drawing dw(fm);


    //creating layout for form
    place.div("<Mycard grid=[4,5] margin=[5,110,5,110] gap=10>");

    static std::map<char, button*> cards;
    std::list<button> buttons;


    //assign image file to my card
    front = nana::paint::image("front.bmp");
    card1 = nana::paint::image("b1.bmp");
    card2 = nana::paint::image("b2.bmp");
    card3 = nana::paint::image("b3.bmp");
    card4 = nana::paint::image("b4.bmp");
    card5 = nana::paint::image("b5.bmp");
    card6 = nana::paint::image("b6.bmp");
    card7 = nana::paint::image("b7.bmp");
    card8 = nana::paint::image("b8.bmp");
    card9 = nana::paint::image("b9.bmp");
    card10 = nana::paint::image("b10.bmp");
    std::vector<paint::image> cardimage;

    //add images to my vector of images
    cardimage.insert(cardimage.end(),card1);
    cardimage.insert(cardimage.end(), card2);
    cardimage.insert(cardimage.end(), card3);
    cardimage.insert(cardimage.end(), card4);
    cardimage.insert(cardimage.end(), card5);
    cardimage.insert(cardimage.end(), card6);
    cardimage.insert(cardimage.end(), card7);
    cardimage.insert(cardimage.end(), card8);
    cardimage.insert(cardimage.end(), card9);
    cardimage.insert(cardimage.end(), card10);
    
    //declaire vector for checking
    std::vector<int> order;
    std::vector<int> randomcheck;
    int position[20] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
    int count = 0;

    int x[40];
    for (int k = 0; k < 40; k++) {
        x[k] = 0;
    }

    
    for (auto i : position) {

        buttons.emplace_front((fm).handle());
        auto& card_btn = buttons.front();
        cards[i] = &card_btn;

        card_btn.icon(front);

        place["Mycard"] << card_btn;
        int choice1, choice2;
        int round = 0;
        card_btn.events().click(pool_push(pool, [&, i]() {
            
            //chose random int
            int j = rand() % 9 + 0;


            //for first image
            if (round == 0) {

                //if button was clicked before this then it enter in this if condition
                if (std::count(order.begin(), order.end(), i)) {
                    count = 1;
                    order.insert(order.end(),i);
                    card_btn.icon(cardimage.at(x[i]));
                    clicked(i);
                    randomcheck.insert(randomcheck.end(),j);
                    player.play();
                    round = 1;
                    choice1 = i;
                    checkimage1 = x[i];
                    std::cout << "i am clicked: 1" << std::endl;
                }

                //if button was not clicke before this then it enter in this condition
                else {

                    //if this int j (this images) already used then it check how many times it used
                    if (std::count(randomcheck.begin(), randomcheck.end(), j)) {
                        
                        //images was used for this times
                        int feq = std::count(randomcheck.begin(), randomcheck.end(), j);

                        //if images was used 2 times already then we can't use this image for again
                        if (feq == 2) {
                            //we chose new int(image) that we never used
                            int check = std::count(randomcheck.begin(), randomcheck.end(), j);
                            while (check!=0) {
                                j = rand() % 9 + 0;
                                check = std::count(randomcheck.begin(), randomcheck.end(), j);
                               
                            }
                            count = 1;
                            order.insert(order.end(),i);
                            card_btn.icon(cardimage.at(j));
                            randomcheck.insert(randomcheck.end(),j);
                            x[i] = j;
                            clicked(i);
                            player.play();
                            round = 1;
                            choice1 = i;
                            checkimage1 = j;
                            std::cout << "i am clicked: 2" << std::endl;
                        }
                        
                        //if image was used only once then it will go inside this condition
                        else {
                            count = 2;
                            order.insert(order.end(),i);
                            card_btn.icon(cardimage.at(j));
                            randomcheck.insert(randomcheck.end(),j);
                            x[i] = j;
                            clicked(i);
                            player.play();
                            round = 1;
                            choice1 = i;
                            checkimage1 = j;
                            std::cout << "i am clicked: 3" << std::endl;
                        }
                    }
                    //if this int j(this image) never used before then it go inside this condition
                    else {
                        order.insert(order.end(),i);
                        card_btn.icon(cardimage.at(j));
                        clicked(i);
                        randomcheck.insert(randomcheck.end(),j);
                        x[i] = j;
                        player.play();
                        count = 1;
                        round = 1;
                        choice1 = i;
                        checkimage1 = j;
                        std::cout << "i am clicked: 4" << std::endl;
                    }
                }
            }
            //same rules for secound round 1
            else {
                if (std::count(order.begin(), order.end(), i)) {
                    count = 2;
                    order.insert(order.end(),i);
                    card_btn.icon(cardimage.at(x[i]));
                    clicked(i);
                    randomcheck.insert(randomcheck.end(),j);
                    player.play();
                    round = 0;
                    choice2 = i;
                    checkimage2 = x[i];
                    
                    if (checkimage1 == checkimage2) {
                        std::cout << "image match" << std::endl;
                        playerwin.play();
                    }
                    else {
                        auto& card_btn1 = buttons.front();
                        cards[choice1] = &card_btn1;
                        card_btn1.icon(front);
                        pyayerloos.play();
                        card_btn.icon(front);
                        std::cout << "image not match" << std::endl;
                    }
                }
                else {
                    if (std::count(randomcheck.begin(), randomcheck.end(), j)) {
                        int feq = std::count(randomcheck.begin(), randomcheck.end(), j);
                        if (feq==2) {
                            while (std::count(randomcheck.begin(), randomcheck.end(), j)) {
                                j = rand() % 9 + 0;
                            }
                            count = 1;
                            order.insert(order.end(),i);
                            card_btn.icon(cardimage.at(j));
                            randomcheck.insert(randomcheck.end(),j);
                            x[i] = j;
                            clicked(i);
                            player.play();
                            round = 0;
                            choice1 = i;
                            checkimage2 = j;
                            
                            std::cout << "i am clicked: 2.1" << std::endl;
                            if (checkimage1 == checkimage2) {
                                std::cout << "image match" << std::endl;
                                playerwin.play();
                            }
                            else {
                                auto& card_btn1 = buttons.front();
                                cards[choice1] = &card_btn1;
                                card_btn1.icon(front);
                                pyayerloos.play();
                                card_btn.icon(front);
                                std::cout << "image not match" << std::endl;
                            }
                        }
                        else {
                            count = 2;
                            order.insert(order.end(),i);
                            card_btn.icon(cardimage.at(j));
                            x[i] = j;
                            clicked(i);
                            randomcheck.insert(randomcheck.end(),j);
                            player.play();
                            round = 0;
                            choice2 = i;
                            checkimage2 = j;
                            
                            std::cout << "i am clicked: 3.1" << std::endl;
                        }
                        if (checkimage1 == checkimage2) {
                            std::cout << "image match" << std::endl;
                            playerwin.play();
                        }
                        else {
                            auto& card_btn1 = buttons.front();
                            cards[choice1] = &card_btn1;
                            card_btn1.icon(front);
                            pyayerloos.play();
                            card_btn.icon(front);
                            std::cout << "image not match" << std::endl;
                        }
                    }
                    else {
                        order.insert(order.end(),i);
                        card_btn.icon(cardimage.at(j));
                        clicked(i);
                        randomcheck.insert(randomcheck.end(),j);
                        x[i] = j;
                        player.play();
                        count = 1;
                        round = 0;
                        choice2 = i;
                        checkimage2 = j;
                        
                        if (checkimage1 == checkimage2) {
                            std::cout << "image match" << std::endl;
                            playerwin.play();
                        }
                        else {
                            auto& card_btn1 = buttons.front();
                            cards[choice1] = &card_btn1;
                            card_btn1.icon(front);
                            pyayerloos.play();
                            card_btn.icon(front);
                            std::cout << "image not match" << std::endl;
                        }
                    }
                }
            }
            }));
    }
    place.collocate();
    fm.show();
    exec();
}
