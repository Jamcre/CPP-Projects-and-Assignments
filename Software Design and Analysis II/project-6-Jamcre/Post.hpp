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
      ENUM used for priority_id_
   */
   enum priority
   {
      LOW = 0,
      MEDIUM = 1,
      HIGH = 2
   };

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

   /**
      @return : returns this posts time_t timestamp
   */
   time_t getTimeT() const;

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

   /**
      @post             : increments the likes_ private member
   */
   void like();

   /**
     @return            : the value of the likes_ private member
   */
   int getLikes() const;

   /**
     @param             :  a priority value
     @post              :  sets the priority_id_ to the value of the parameter
   */
   void setPriority(const priority new_priority);

   /**
      @return             :  the value of the priority_id_ data member
   */
   priority getPriority() const;

private:
   std::string post_title_;
   std::string post_body_;
   time_t time_stamp_;
   std::string username_;
   int likes_ = 0;
   priority priority_id_ = MEDIUM;

}; // end Post

#endif
