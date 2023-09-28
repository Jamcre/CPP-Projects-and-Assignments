/****************************************************************************************************************************
Title         :   Post.hpp
Author        :   Dream Team
Description   :   header/interface for Post class
****************************************************************************************************************************/

#ifndef POST_
#define POST_

#include <iostream>
#include <string>
#include <time.h>

class Post
{
public:
   /**
      Parameterized constructor.
      @param      : The title of the post (a string)
      @param      : The body content of the post (a string)
      @param      : The username of the Account that added this post (a string)

      @post         : Sets the title, body and username to the value of the parameters
                      It will also generate the current time and store it
   */
   Post(std::string title, std::string body, std::string username);

   /**
      @return : the title of the Post
   */
   std::string getTitle() const;

   /**
     @param  : a reference to title of the Post
     @post   : sets the private data member to the value of the parameter
   */
   void setTitle(const std::string &title);

   /**
      @return : the body of the Post
   */
   std::string getBody() const;

   /**
      @param  : a reference to body of the Post
      @post   : sets the private data member to the value of the parameter
   */

   void setBody(const std::string &body);

   /**
      Accessor Function
      @return       : username associated with this Post
   */
   std::string getUsername() const;

   /**
      Mutator Function
      @param        : a reference to the username associated with this Post
      @post   : sets the private data member to the value of the parameter
   */
   void setUsername(const std::string &username);

   /**
      @post   : prints the time the Post was created to the standard output as asctime(localtime(&time_stamp_))
   */
   void getTimeStamp() const;

   /**
      Mutator Function
      @post   : sets the private data member to the current time
   */
   void updateTimeStamp();

   void virtual displayPost() = 0;

   /**
      @param            : The Post object to compare
      @return           : true if this Post's username is less than the parameter
                          Post username, false otherwise
   */
   bool operator<(const Post &a_post) const;

   /**
      @param            : The Post object to compare
      @return           : true if this Post's username is greater than the
                          parameter Post username, false otherwise
   */
   bool operator>(const Post &a_post) const;

private:
   std::string post_title_;
   std::string post_body_;
   time_t time_stamp_;
   std::string username_;

}; // end Post

#endif
