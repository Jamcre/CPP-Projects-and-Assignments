---  
layout: myDefault
title: PROJECT 2
---  

# Project 2: Show me the money - Inheritance

![social_media](./entreprenuer.jpeg)

_**The saga continues. You are on your way to own a social media platform. The next step in your venture is to facilitate interaction on the platform, as well as allowing monetized posts to incentivize consistent engagement and product placement.**_

In this project you will create three additional classes that inherit from the `Post` class.   



### Access the assignment in GitHub Classroom:
This is the link to accept this assignment on GitHub Classroom:
https://classroom.github.com/a/SfBC40nr

---

### Some additional resources on Inheritance and Regular Expression

-   [Code Beauty on inheritance programming](https://youtu.be/-W-TYjL0aFE)
-   [Caleb Curry on base and subclass inheritance](https://youtu.be/_rzEUwv2-eQ)
-   [Regular Expression in C++](https://cplusplus.com/reference/regex/)
-   [Validating Regex as a link](https://stackoverflow.com/questions/5620235/cpp-regular-expression-to-validate-url)

---

### Implementation:


**Work incrementally!** Work through the tasks sequentially (implement and test). Only move on to a task when you are positive that the previous one has been completed correctly. Remember that the **function names, returns, parameters, pre and post conditions must be exactly as specified in this project specification**. This is a contract, it gives you all the information necessary to complete this assignment correctly. If you don't understand this project specification and its requirements, ask for clarification before you proceed. _Remember to make parameters and functions read-only when appropriate._

---

## Task 0: Usernames
The `Post` class **must** have the following **additional** _private member variables_:
```
A string representing the username of the Account that created it.  
This will be useful in future projects.
```

The `Post` class **must** have the additional accessor and mutator _public member functions_:
```
/*
   Accessor Function
   @return       : username associated with this Post
*/
getUsername

/*
   Mutator Function
   @param        : a reference to the username associated with this Post
*/
setUsername
```


## Task 1: Please subscribe and hit that **Like** button
Define and implement the `General` class as a **subclass** of `Post` (i.e. `General` inherits from `Post` it's public members).

### Data and Types

The `General` class **must** have the following _type_:
 ```
 * An Enum named Reactions with constants: LIKE, DISLIKE, LAUGH, WOW, SAD and ANGRY.
  ```

The `General` class **must** have the following _private member variables_:

```
   * An integer array of size 6 that, indexed by Reactions, will store the number of reactions of each type the post has received.   

   For example, the first element in the array will record how many reactions of type LIKE the post has received,  
   the second element will record the number of DISLIKE reactions the post has received, and so on.

```

The `General` class **must** have the following _public member functions_:

### Constructors

```
   /**
      Parameterized constructor.
        @param    : The name of the General post
        @param    : The body of the General post

        @post     : Sets the title and body of the General post to the parameters.
                    It will also generate the current time and store it
                    and it initializes the array with default values
   */
```
***IMPORTANT:*** keep in mind the order in which constructors are called, which are superclass members and which are subclass members.

### Unique methods

```
   /**
      Mutator function to add a reaction
      @param    : A reference to reaction (represented by a value of type Reaction)
      @return   : return True if the react to the post is successful or false
                  if the reaction provided is not within a valid Reaction value.

      @post     : Increments the array at the index corresponding to the input Reaction
   */
   reactToPost

   /**
      @post     : Prints the reaction to the post in this format (example):
                  Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
   */
   getReactions
```

### Displaying

```
   /**
      @post     : Displays the General post (example):
                  \n
                  {post_title_} at {time_stamp_}:
                  {post_body_}
                  \n
                  Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
                  \n
   */
   displayPost  
```


---

## Task 2: And the results are in.....
Define and implement the `Poll` class as a **subclass** of `Post` (i.e. `Poll` inherits from `Post` it's public members).

### Data and Types

The `Poll` class **must** have the following _private member variables_:

```
   * A vector of strings containing the poll options
   * A vector of integers containing the number of votes for each poll option,   
   where the integer in the first position indicates the number of votes for the poll option
   in the first position , the second integer indicates the number of votes for the second
   poll option, etc.
   Note that, by this definition, the two vectors will have same size!
```


The `Poll` class **must** contain _public member functions_ that do the following:

### Constructors

```
   /**
      Parameterized constructor.
        @param    : The title of the Poll post
        @param    : The question of the Poll post
        @param    : A vector of options for the Poll post

        @post     :Sets the title and body of the Poll post to what was passed by the user.
                   It will also generate the current time and store it and will initialize the vectors of options and their respective number of votes.
   */
```
***IMPORTANT:*** keep in mind the order in which constructors are called, which are superclass members and which are subclass members.


### Unique methods

```

   /**

         @param     : a reference to int between 0 < number of options
         @return    : True if index is within range and we can vote for a poll,
                      false otherwise
         @post      : Increments the poll votes based on the index which
                      will refer to the index in the poll options
   */
   votePoll


   /**
      Mutator function used to either add a poll or change one of the poll options
         @param     : A reference to the new poll option
         @param     : A reference to int that can either represent the index of the
                      existing option that will be replaced
                      or if choice_number > current number of options,
                      it will add this new option to the poll.

        @post       : Resets the number of votes for this option.
   */
   changePollOption


   /**
      Accessor function
        @post       : prints the reaction to the post in this format
                    (example where option_n is the string at position n in the poll options vector):
                    0 votes for: option_1
                    5 votes for: option_2
                    2 votes for: option_3
                    ...
   */
   getPollOptions()


   /**
      Accessor function
      @param      : The index of the option
      @return     : returns the number of votes for a given option
   */
   getPollVotes
```

### Displaying

```
   /**
      @post   : displays the whole Poll post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                0 votes for: option_1
                5 votes for: option_2
                2 votes for: option_3
                ...
                \n
   */
   displayPost  
```


---

## Task 3: Please disable Adblock before continuing
Define and implement the `Promotional` class as a **subclass** of `Post` (i.e. `Promotional` inherits from `Post` it's public members).


### Data and Types

The `Promotional` class **must** have the following _private member variables_:

```
   string that represents a url
```

The `Promotional` class **must** contain _public member functions_ that do the following:

### Constructors

```
   /**
      Parameterized constructor.
         @param       : The name of the Promotional post
         @param       : The body of the Promotional post
         @param       : The link of the Promotional post

        @post         : Sets the title, body and link (if it's a proper link otherwise "Broken Link")
                       of the Promotional post to what was passed by the user.
                       It will also generate the current time and store it.
   */
```

***IMPORTANT:*** keep in mind the order in which constructors are called, which are superclass members and which are subclass members.


### Unique methods

```
   /**
      Accessor function
      @return         : Returns the post link
   */
   getLink




   /**
      @param    : A reference to the link that is in the format 'https://www.something.something'
                  or 'http://www.something.something' with the last 'something' being at least 2 characters
      @return   : true if the link is correctly formatted, false otherwise

      @post     : If the link is not correctly formatted, store "Broken Link"
                  in the link member variable, otherwise store the value of the
                  parameter (Hint: see <regex>)
   */
   setLink
```

### Displaying

```
   /**
      @post      : displays the entire Promotional post (example):
                  \n
                  {post_title_} at {time_stamp_}:
                  {post_body_}
                  \n
                  {link}
                  \n
   */
   displayPost  
```

---

### Submission:
**You will submit your solution to Gradescope via GitHub Classroom (see video linked above). The autograder will grade the following files only**:  
`Promotional.hpp Promotional.cpp Poll.hpp Poll.cpp General.hpp General.cpp Post.hpp Post.cpp`

Your project must be submitted to Gradescope through GitHub Classroom. Although Gradescope allows multiple submissions, it is not a platform for testing and/or debugging and it should not be used for that. You MUST test and debug your program locally. Before submitting to Gradescope you MUST ensure that your program compiles using the provided makefile and runs correctly on the Linux machines in the labs at Hunter (see detailed instructions on how to upload, compile and run your files in the “Programming Guidelines” document). That is your baseline, if it runs correctly there it will run correctly on Gradescope, and if it does not, you will have the necessary feedback (compiler error messages, debugger or program output) to guide you in debugging, which you don’t have through Gradescope. **“But it ran on my machine!” is not a valid argument for a submission that does not compile.** Once you have done all the above you submit it to Gradescope.

---

### Testing
How to compile in your **Makefile**:   
In terminal, in the same directory as your *Makefile and your source files*, use the following command
```
make rebuild
```

This assumes you did not rename the `Makefile` and that it is the only one in the current directory.


You must always implement and test you programs **INCREMENTALLY!!!**
What does this mean? Implement and test one method at a time.
**For each class**
- Implement one function/method and test it thoroughly (multiple test cases + edge cases if applicable).
- Implement the next function/method and test in the same fashion.
**How do you do this?** Write your own `main()` function to test your classes. In this course you will never submit your test program, but you must always write one to test your classes. Choose the order in which you implement your methods so that you can test incrementally: i.e. implement mutator functions before accessor functions. Sometimes functions depend on one another. If you need to use a function you have not yet implemented, you can use stubs: a dummy implementation that always returns a single value for testing.  Don’t forget to go back and implement the stub!!! If you put the word STUB in a comment, some editors will make it more visible.

### Grading Rubrics
**Correctness 80%** (distributed across unit testing of your submission)  
**Documentation 10%**  
**Style and Design 10%** (proper naming, modularity, and organization)  

### Due date:

This project is **due on September 23**
No late submissions will be accepted.

---

### Important
You must start working on the projects as soon as they are assigned to detect any problems and to address them with us **well before** the deadline so that we have time to get back to you **before** the deadline.
**There will be no extensions and no negotiation about project grades after the submission deadline.**



*Credits: Tiziana Ligorio, Violent Hajdini, Yash Mahtani*
