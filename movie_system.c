#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM_MOVIES 1000000
#define MAX_LINE_LENGTH 100000



typedef struct {
    int movieID;
    char originalLanguage[50];
    char originalTitle[255];
    char englishTitle[500];
    double budget;
    double revenue;
    char homepage[500];
    int runtime;
    char releaseDate[11];
    char genres[200];
    char productionCompanies[500];
    char productionCountries[500];
    char spokenLanguages[500];
} Movie;

// Function prototypes
Movie* loadMovies();
void addMovie(Movie *movies, int *numMovies);
void removeMovie(Movie *movies, int *numMovies);
void searchByID(const Movie *movies, int numMovies);
void searchByGenre(const Movie *movies, int numMovies, const char *genre);
void printAllInformation(const Movie *movies, int numMovies);
void printTotalNumMovies(const Movie *movies, int numMovies);
void writeToFile(const Movie *movies, int numMovies, const char *filename);

// Main function
int main() {

      FILE *file = fopen("Movies.csv", "r");
      if (file == NULL)
      {
          perror("Error opening file");
        return 1;
      }

      int numMovies = 0;
      char buffer[5000];
      while (fgets(buffer, sizeof(buffer), file) != NULL)
      {
          numMovies++;
      }
  
      fclose(file);

      Movie * movies = loadMovies(numMovies);



  while (1)
  {
      printf("\n\n1-Display the Movie Information\n");
      printf("2-Add a movie to the list\n");
      printf("3-Remove a movie from the list\n");
      printf("4-Search a movie by its ID\n");
      printf("5-Print total number of movies\n");
      printf("6-Write to the file\n");
      printf("0-Save and Quit\n");


      int option;
      printf("\n\nOPTION: ");

      scanf("%d", &option);
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
      {
      }

      if (option == 1)
        printAllInformation(movies, 50);
      else if (option == 2)
        addMovie(movies, &numMovies);
      else if (option == 3)
      {
        removeMovie(movies, &numMovies);
      }
      else if (option == 4)
        searchByID(movies, numMovies);
      else if (option == 5)
      {
        printTotalNumMovies(movies, numMovies);
      }
      else if (option == 6)
        writeToFile(movies, numMovies, "output.txt");
      else if (option == 0)
      {
          break;
      }

      else
          printf("Wrong Option");
  }



    //addMovie(movies, &numMovies);
    //removeMovie(movies, &numMovies);
    //searchByID(movies, numMovies);
    //searchByGenre(movies, numMovies, "Action");
    //printAllInformation(movies, 10);
    //printTotalNumMovies(movies, numMovies);
    //writeToFile(movies, numMovies, "output.txt");
    
    free(movies);

    return 0;
}


Movie *loadMovies()
{
    
    Movie *movies = (Movie *)malloc(MAX_NUM_MOVIES * sizeof(Movie));

    FILE* file = fopen("Movies.csv", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    
    char line[4000];
    fgets(line, 4000, file);

    int count = 0;
    while (fgets(line, 4000, file) != NULL)
    {
        // Split the line into fields
        char *field = strtok(line, ",");
        int fieldIndex = 0;

       
        char fields[13][500];
        while (field != NULL && fieldIndex < 13)
        {
            strcpy(fields[fieldIndex], field);
            field = strtok(NULL, ",");
            fieldIndex++;
        }

        Movie temp;

        temp.movieID = atoi(fields[0]);
        strcpy(temp.originalLanguage, fields[1]);
        strcpy(temp.originalTitle, fields[2]);
        strcpy(temp.englishTitle, fields[3]);
        temp.budget = atof(fields[4]);
        temp.revenue = atof(fields[5]);
        strcpy(temp.homepage, fields[6]);
        temp.runtime = atoi(fields[7]); 
        strcpy(temp.releaseDate, fields[8]);
        strcpy(temp.genres, fields[9]);
        strcpy(temp.productionCompanies, fields[10]);
        strcpy(temp.productionCountries, fields[11]);
        strcpy(temp.spokenLanguages, fields[12]);

        movies[count] = temp;

        count++;
    }

    fclose(file);
    return movies;
}



void addMovie(Movie *movies, int *numMovies) {
    // Check if there is enough space for a new movie
    if (*numMovies >= MAX_NUM_MOVIES) {
        printf("Cannot add more movies. Maximum limit reached.\n");
        return;
    }

    // Get user input for the new movie
    printf("Enter details for the new movie:\n");

    printf("Movie ID: ");
    scanf("%d", &movies[*numMovies].movieID);

    printf("Original Language: ");
    scanf("%s", movies[*numMovies].originalLanguage);

    printf("Original Title: ");
    scanf("%s", movies[*numMovies].originalTitle);

    printf("English Title: ");
    scanf("%s", movies[*numMovies].englishTitle);

    printf("Budget: ");
    scanf("%lf", &movies[*numMovies].budget);

    printf("Revenue: ");
    scanf("%lf", &movies[*numMovies].revenue);

    printf("Homepage: ");
    scanf("%s", movies[*numMovies].homepage);

    printf("Runtime: ");
    scanf("%d", &movies[*numMovies].runtime);

    printf("Release Date: ");
    scanf("%s", movies[*numMovies].releaseDate);

    printf("Genres: ");
    scanf("%s", movies[*numMovies].genres);

    printf("Production Companies: ");
    scanf("%s", movies[*numMovies].productionCompanies);

    printf("Production Countries: ");
    scanf("%s", movies[*numMovies].productionCountries);

    printf("Spoken Languages: ");
    scanf("%s", movies[*numMovies].spokenLanguages);

    // Open the file in append mode
    FILE *file = fopen("Movies.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the new movie information to the file
    fprintf(file, "%d,%s,%s,%s,%.2f,%.2f,%s,%d,%s,%s,%s,%s,%s\n",
            movies[*numMovies].movieID, movies[*numMovies].originalLanguage,
            movies[*numMovies].originalTitle, movies[*numMovies].englishTitle,
            movies[*numMovies].budget, movies[*numMovies].revenue,
            movies[*numMovies].homepage, movies[*numMovies].runtime,
            movies[*numMovies].releaseDate, movies[*numMovies].genres,
            movies[*numMovies].productionCompanies, movies[*numMovies].productionCountries,
            movies[*numMovies].spokenLanguages);

    // Close the file
    fclose(file);

    // Increment the number of movies
    (*numMovies)++;
    printf("Movie added successfully!\n");
}




void removeMovie(Movie *movies, int *numMovies) {
    int movieID;

    // Get user input for the movie ID to be removed
    printf("Enter the Movie ID to be removed: ");
    scanf("%d", &movieID);

    int index = -1;  // Initialize index to an invalid value

    // Find the index of the movie with the given ID
    for (int i = 0; i < *numMovies; i++) {
        if (movies[i].movieID == movieID) {
            index = i;
            break;
        }
    }

    // Check if the movie with the given ID was found
    if (index != -1) {
        // Shift elements to remove the movie from the array
        for (int i = index; i < (*numMovies - 1); i++) {
            movies[i] = movies[i + 1];
        }
        //movies[numMovies-1]=NULL;

        
        (*numMovies)--;
        printf("Movie with ID %d removed successfully!\n", movieID);
    } else {
        printf("Movie with ID %d not found.\n", movieID);
    }
}


void searchByID(const Movie *movies, int numMovies) {
  int movieID;

  // Get user input for the movie ID to be removed
  printf("Enter the Movie ID to : ");
  scanf("%d", &movieID);
  

  for ( int i=0; i<numMovies; i++) {
    if(movieID == movies[i].movieID){
      printf("Movie found!\n");
      printf("Movie ID: %d\n", movies[i].movieID);
      printf("Original Language: %s\n", movies[i].originalLanguage[0] ? movies[i].originalLanguage : "Unknown");
      printf("Original Title: %s\n", movies[i].originalTitle[0] ? movies[i].originalTitle : "Not available");
      printf("English Title: %s\n", movies[i].englishTitle[0] ? movies[i].englishTitle : "Not available");
      printf("Budget: %.2f\n", movies[i].budget != 0.00 ? movies[i].budget : 0.0);
      printf("Revenue: %.2f\n", movies[i].revenue != 0.00 ? movies[i].revenue : 0.0);
      printf("Homepage: %s\n", movies[i].homepage[0] ? movies[i].homepage : "Not available");
      printf("Runtime: %d minutes\n", movies[i].runtime);
      printf("Release Date: %s\n", movies[i].releaseDate[0] ? movies[i].releaseDate : "Not available");
      printf("Genres: %s\n", movies[i].genres[0] ? movies[i].genres : "Not available");

      printf("Production Companies: %s\n", movies[i].productionCompanies[0] ? movies[i].productionCompanies : "Not available");
      printf("Production Countries: %s\n", movies[i].productionCountries[0] ? movies[i].productionCountries : "Not available");
      printf("Spoken Languages: %s\n", movies[i].spokenLanguages[0] ? movies[i].spokenLanguages : "Not available");

      printf("-----------------------------------\n");
    }

      }
}

void searchByGenre(const Movie *movies, int numMovies, const char *genre) {
    // strcmp
}

void printAllInformation(const Movie *movies, int numMovies) {
    printf("\nAll Movie Information:\n");

    for (int i = 0; i < numMovies-1; i++) {
        printf("Movie ID: %d\n", movies[i].movieID);
        printf("Original Language: %s\n", movies[i].originalLanguage[0] ? movies[i].originalLanguage : "Unknown");
        printf("Original Title: %s\n", movies[i].originalTitle[0] ? movies[i].originalTitle : "Not available");
        printf("English Title: %s\n", movies[i].englishTitle[0] ? movies[i].englishTitle : "Not available");
        printf("Budget: %.2f\n", movies[i].budget != 0.00 ? movies[i].budget : 0.0);
        printf("Revenue: %.2f\n", movies[i].revenue != 0.00 ? movies[i].revenue : 0.0);
        printf("Homepage: %s\n", movies[i].homepage[0] ? movies[i].homepage : "Not available");
        printf("Runtime: %d minutes\n", movies[i].runtime);
        printf("Release Date: %s\n", movies[i].releaseDate[0] ? movies[i].releaseDate : "Not available");
        printf("Genres: %s\n", movies[i].genres[0] ? movies[i].genres : "Not available");

        printf("Production Companies: %s\n", movies[i].productionCompanies[0] ? movies[i].productionCompanies : "Not available");
        printf("Production Countries: %s\n", movies[i].productionCountries[0] ? movies[i].productionCountries : "Not available");
        printf("Spoken Languages: %s\n", movies[i].spokenLanguages[0] ? movies[i].spokenLanguages : "Not available");

        printf("-----------------------------------\n");
    }
}


void printTotalNumMovies(const Movie *movies, int numMovies) {
    printf("Number of Movies: %d\n", numMovies);
}

void writeToFile(const Movie *movies, int numMovies, const char *filename) {
    FILE *file = fopen("test.csv", "w");
    char buff[500];

    fprintf(file,"MovieID,OriginalLanguage,OriginalTitle,EnglishTitle,Budget,Revenue,Homepage,Runtime,ReleaseDate,Genres,ProductionCompanies,ProductionCountries,SpokenLanguages\n",300);
    for (int i = 0; i < numMovies; i++) {
      fprintf(file, "%d,%s,%s,%s,%.1f,%.1f,%s,%d,%s,%s,%s,%s,%s", movies[i].movieID, movies[i].originalLanguage, movies[i].originalTitle, movies[i].englishTitle, movies[i].budget, movies[i].revenue, movies[i].homepage, movies[i].runtime, movies[i].releaseDate,movies[i].genres,movies[i].productionCompanies,movies[i].productionCountries,movies[i].spokenLanguages,4000);
    }
}
