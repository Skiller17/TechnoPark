#include <gtest/gtest.h>
#include "ActorTitles.h"
#include "NonAdultMovies.h"
#include "NamesOfTitles.h"


TEST(TestActorTitles, SuccessSearchTItles) {
    std::string title = "nm0000001\tFred Astaire\t1899\t1987\tsoundtrack,actor,miscellaneous\ttt0045537,tt0050419,tt0053137,tt0072308";
    std::vector<std::string> testIdMovies = {" tt0045537", " tt0050419", " tt0053137", " tt0072308"};

    ActorTitles actorTitles;

    actorTitles.SearchTitles(title);

    EXPECT_EQ(actorTitles.idMovie, testIdMovies);
}

TEST(TestActorTitles, UndefinedTItles) {
    std::string title = "nm0000001\tFred Astaire\t1899\t1987\tsoundtrack,actor,miscellaneous\t";
    std::vector<std::string> testIdMovies = {" "};

    ActorTitles actorTitles;

    actorTitles.SearchTitles(title);

    EXPECT_EQ(actorTitles.idMovie, testIdMovies);
}

TEST(TestNonAdultMovies, SuccessSearchNonAdultsMovies) {
    std::string testInformationAboutTitle = "tt0045537\tmovie\tThe Band Wagon\tThe Band Wagon\t0\t1953\t\\N\t112\tComedy,Musical,Romance ";
    std::vector<std::string> testNonAdultMovie = {"tt0045537"};

    NonAdultMovies nonAdultMovies;
    nonAdultMovies.idMovie = {" tt0045537", " tt0050419", " tt0053137", " tt0072308"};

    nonAdultMovies.SearchNonAdultMovies(testInformationAboutTitle);

    EXPECT_EQ(nonAdultMovies.nonAdultMovie, testNonAdultMovie);
}

TEST(TestNonAdultMovies, NoFindNonAdultsMovies) {
    std::string testInformationAboutTitle = "tt0045537\tmovie\tThe Band Wagon\tThe Band Wagon\t1\t1953\t\\N\t112\tComedy,Musical,Romance ";
    std::vector<std::string> testNonAdultMovie = {};

    NonAdultMovies nonAdultMovies;
    nonAdultMovies.idMovie = {" tt0045537", " tt0050419", " tt0053137", " tt0072308"};

    nonAdultMovies.SearchNonAdultMovies(testInformationAboutTitle);

    EXPECT_EQ(nonAdultMovies.nonAdultMovie, testNonAdultMovie);
}

TEST(TestNonAdultMovies, UndefinedNonAdultsMovies) {
    std::string testInformationAboutTitle = "tt0045537\tmovie\tThe Band Wagon\tThe Band Wagon\t \t1953\t\\N\t112\tComedy,Musical,Romance ";
    std::vector<std::string> testNonAdultMovie = {};

    NonAdultMovies nonAdultMovies;
    nonAdultMovies.idMovie = {" tt0045537", " tt0050419", " tt0053137", " tt0072308"};

    nonAdultMovies.SearchNonAdultMovies(testInformationAboutTitle);

    EXPECT_EQ(nonAdultMovies.nonAdultMovie, testNonAdultMovie);
}

TEST(TestNamesOfTitles, SuccessSearchRuTitlesNames) {
    std::string testLocalizedTitles = "tt0045537\t15\tТеатральный фургон\tSUHH\tru\timdbDisplay\t\\N\t0";
    std::vector<std::string> testRuTitlesNames = {" Театральный фургон"};
    std::vector<std::string> testRuLocalizedTitles = {"tt0045537", "tt0050419", "tt0053137", "tt0072308"};

    NamesOfTitles namesOfTitles;

    namesOfTitles.SearchRuTitlesNames(testLocalizedTitles, testRuLocalizedTitles);

    EXPECT_EQ(namesOfTitles.ruTitlesNames, testRuTitlesNames);
}

TEST(TestNamesOfTitles, NoFindRuTitlesNames) {
    std::string testLocalizedTitles = "tt0045537\t15\tThe band Wagon\tEU\tru\timdbDisplay\t\\N\t0";
    std::vector<std::string> testRuTitlesNames = {};
    std::vector<std::string> testRuLocalizedTitles = {"tt0045537", "tt0050419", "tt0053137", "tt0072308"};

    NamesOfTitles namesOfTitles;

    namesOfTitles.SearchRuTitlesNames(testLocalizedTitles, testRuLocalizedTitles);

    EXPECT_EQ(namesOfTitles.ruTitlesNames, testRuTitlesNames);
}

TEST(TestNamesOfTitles, SuccessSearchNoRuTitlesNames) {
    std::string testLocalizedTitles = "tt0045537\t12\tThe Band Wagon\t\\N\t\\N\toriginal\t\\N\t1";
    std::vector<std::string> testNoRuTitlesNames = {" The Band Wagon"};
    std::vector<std::string> testNoRuLocalizedTitles = {"tt0045537", "tt0050419", "tt0053137", "tt0072308"};

    NamesOfTitles namesOfTitles;

    namesOfTitles.SearchNoRuTitlesNames(testLocalizedTitles, testNoRuLocalizedTitles);

    EXPECT_EQ(namesOfTitles.noRuTitlesNames, testNoRuTitlesNames);
}

TEST(TestNamesOfTitles, NoFindNoRuTitlesNames) {
    std::string testLocalizedTitles = "tt0045537\t12\tWagonya\t\\N\t\\N\tnoOriginal)\t\\N\t1";
    std::vector<std::string> testNoRuTitlesNames = {};
    std::vector<std::string> testNoRuLocalizedTitles = {"tt0045537", "tt0050419", "tt0053137", "tt0072308"};

    NamesOfTitles namesOfTitles;

    namesOfTitles.SearchNoRuTitlesNames(testLocalizedTitles, testNoRuLocalizedTitles);

    EXPECT_EQ(namesOfTitles.noRuTitlesNames, testNoRuTitlesNames);
}