//
//  main.cpp
//  MySQLCPPConnection
//
//  Created by Zhimin Gao on 10/21/19.
//  Copyright © 2019 Zhimin Gao. All rights reserved.
//
//  Database Project - Javoris Brown S00333473
//

#include <iostream>
#include <mysqlx/xdevapi.h>
#include <fstream>
#include <string>
#include <sstream>   

#include <stdio.h>
#include <stdlib.h>

using ::std::cout;
using ::std::endl;
using ::std::cin;
using ::std::fstream;
using namespace ::mysqlx;

void HW();
void userInput();
void showMenu();
void runQuery(int queryNum);

int main(int argc, const char* argv[])
{
    userInput();

    system("pause");
    return 0;
}

void userInput() {

    int menuNum;
    showMenu();

    cout << "Enter menu number: ";
    cin >> menuNum;

    while (!cin.good() || menuNum < 0 || menuNum > 4) {

        if (menuNum == 0) { break; }

        cout << "Enter menu number: ";

        cin.clear();
        cin.ignore();

        cin >> menuNum;
    }

    if (menuNum != 0) { runQuery(menuNum); }
}

void runQuery(int queryNum) {

    try {
        // connect to sql server
        Session sess("localhost", 33060, "infernokun", "RAINBOWsixSIEGE##11");

        // use a database
        sess.sql("use taco").execute();

        // Query one
        if (queryNum == 1) {

            // execute needed sql command
            RowResult myResult = sess.sql("select primaryTitle, lang, region, avg_rating, votes from ratings inner join title_basics on ratings.ID = title_basics.tconst inner join akas on ratings.ID = akas.titleID where avg_rating > 7 and votes > 1000 AND akas.isOriginalTitle = 1;").execute();

            int count = 0;
            for (Row row : myResult) {
                if (count == 10) {
                    break;
                }

                cout << "Title: " << row[0] << "\tLanguage: " << row[1] << "\tRegion: " << row[2] << "\tRating: " << row[3] << "\tVotes: " << row[4] << endl;
                count++;
            }
        }

        // Query Two
        else if (queryNum == 2) {

            // execute needed sql command
            RowResult myResult = sess.sql("select primaryName, count(*) as moviesDirected from name_basics inner join crew where name_basics.nconst = crew.directors group by primaryName having moviesDirected > 10;").execute();

            int count = 0;

            for (Row row : myResult) {
                if (count == 10) {
                    break;
                }

                cout << "Name: " << row[0] << "\t Movies Directed: " << row[1] << endl;
                count++;
            }
        }

        // Query 3
        else if (queryNum == 3) {

            // execute needed sql command
            RowResult myResult = sess.sql("select primaryTitle, avg_rating, seasonNumber from title_basics inner join ratings on title_basics.tconst = ratings.ID inner join episode on ratings.ID = episode.tconst where seasonNumber > 1 and title_basics.titleType = 'tvEpisode' order by avg_rating desc limit 10;").execute();

            for (Row row : myResult) {

                cout << "Title: " << row[0] << "\tRating: " << row[1] << "\tSeason Number: " << row[2] << endl;
            }
        }

        // Query 4
        else if (queryNum == 4) {

            // execute needed sql command
            RowResult myResult = sess.sql("select primaryTitle, avg_rating, votes from title_basics inner join ratings on title_basics.tconst = ratings.ID where title_basics.startYear > 2015 and title_basics.titleType = 'movie' and title_basics.genre like '%Animation%' and ratings.votes > 10000 order by ratings.avg_rating desc limit 10;").execute();

            for (Row row : myResult) {

                cout << "Title: " << row[0] << "\tRating: " << row[1] << "\tVotes: " << row[2] << endl;
            }
        }
    }

    catch (const mysqlx::Error & err) { cout << "ERROR: " << err << endl; }
    catch (std::exception & ex) { cout << "STD EXCEPTION: " << ex.what() << endl; }
    catch (const char* ex) { cout << "EXCEPTION: " << ex << endl; }

    userInput();
}

void showMenu() {

    cout << "1 - Query #1" << endl;
    cout << "2 - Query #2" << endl;
    cout << "3 - Query #3" << endl;
    cout << "4 - Query #4" << endl;
    cout << "0 - Exit" << endl;
}
