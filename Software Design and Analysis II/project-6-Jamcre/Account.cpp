/****************************************************************************************************************************
Title         :   Account.hpp
Author        :   Dream Team
Description   :   header/interface files for Account class
****************************************************************************************************************************/

#include "Account.hpp"

// default constructor
//@post:  set username and password to ""
//         creates an empty vector of post objects to store into feed_
Account::Account()
{
  username_ = "";
  password_ = "";
  posts_ = LinkedList<Post *>();
  following_ = {};
}

/**
    Parameterized Constructor
    @param username  : username of the account, stored into username_
    @param password  : password of the account, stored into password_
    @post:             sets the private members to the value of the parameters
*/
Account::Account(std::string username, std::string password) : username_(username), password_(password), posts_(LinkedList<Post *>()), following_({}), net_(nullptr) {}

/**
  @return:     the username of the Account
*/
std::string Account::getUsername() const { return username_; }

/**
  @param:     a reference to the username of the Account
  @psot:      sets the parameter to the value of the private member
*/
void Account::setUsername(const std::string &username) { username_ = username; }

/**
  @return:     the password of the Account
*/
std::string Account::getPassword() const { return password_; }

/**
  @param a reference to the password of the Account
  @post:      sets the private member to the value of the parameter
*/
void Account::setPassword(const std::string &password) { password_ = password; }

/**
      Accessor function
      @return           :   the pointer to the Network the account is in
   */
Network<Account> *Account::getNetwork() const { return net_; }

/**
      Mutator function
      @param            :   a pointer to a Network
      @post             :   the Network pointer private member points to the input Network
   */
void Account::setNetwork(Network<Account> *network) { net_ = network; }

/**
    @param newPost   : The pointer to the Post object that will be added to its list
    @return          : Will return true if a post gets added sucesfully to the vector

    @post:           " Adds post to posts_ and its Networks feed_
*/
bool Account::addPost(Post *newPost)
{
  posts_.insert(newPost, 0);
  net_->addToFeed(newPost);

  // adding and ordering for min liked post
  AddPostForMinMaxLikes(newPost);

  return true;
}

/*
    @post:      Prints the feed_ that contains the post objects by calling their display function
*/
void Account::viewPosts() const
{

  Node<Post *> *itt = posts_.getHeadPtr();

  while (itt != nullptr)
  {
    itt->getItem()->displayPost();
    itt = itt->getNext();
  }
}

/**
      @param            :   the username of the Account to follow
      @return           :   true if the account was successfully able to follow, false otherwise
      @post             :   adds the username to the vector of following accounts only if
                            it is affiliated to a Network AND it is not already following an account
                            with the same username.
   */
bool Account::followAccount(const std::string username)
{

  bool exists = false;

  for (std::string un : following_)
  {
    if (un == username)
    {
      exists = true;
    }
  }

  if (!exists && net_ != nullptr)
  {
    following_.push_back(username);
    return true;
  }

  return false;
}

/**
      @return           :   the vector of usernames the Account is following
   */
std::vector<std::string> Account::viewFollowing() const
{
  return following_;
}

/**
  @return           :  true if account has same private members as parameter,
                       false otherwise
*/
bool Account::operator==(const Account &acc) const
{
  if (acc.getUsername() == this->username_ && acc.getPassword() == this->password_)
  {
    return true;
  }

  return false;
}

/*
@param            :   A pointer to a Post
@return           :   True iff the Post was successfully found and removed,
                      false othewise.
@post             :   Removes the given Post from its list
                      as well as from the Network's feed.
*/
bool Account::removePost(Post *post)
{
  int postPosition = posts_.getIndexOf(post);

  if (postPosition > -1)
  {
    posts_.remove(postPosition);
    net_->removePostFromFeed(post);

    std::stack<Post *> temp_stack;
    while (post != min_max_likes_.front())
    {
      temp_stack.push(min_max_likes_.front());
      min_max_likes_.pop_front();
    }
    min_max_likes_.pop_front();
    while (!temp_stack.empty())
    {
      min_max_likes_.push_front(temp_stack.top());
      temp_stack.pop();
    }
    return true;
  }
  return false;
}

/*
@param            :   Pointer to a Post object
@param            :   The new title of the Post (or an empty string if you do not
                      want to change it)
@param            :   The new body of the Post (or an empty string if you do not
                      want to change it)

@post            :   This function will take the Post and given the new title and body,
                     update the Posts title and body as appropriate. It will also update
                     the `timestamp_` to the current time of the update. This function should then
                     update the location of the Post in its list of `posts_` to the front of the list
                     as well as utilizing its Network pointer to do the same in the `feed_`.
*/
bool Account::updatePost(Post *post, std::string new_title, std::string new_body)
{
  if (new_title != "")
  {
    post->setTitle(new_title);
  }
  if (new_body != "")
  {
    post->setBody(new_body);
  }
  post->updateTimeStamp();

  // move the updated post to the front of linked list, because it is most recent post
  Post *temp = post;
  posts_.remove(posts_.getIndexOf(post));
  posts_.insert(temp, 0);
  temp = NULL;

  // empty out the min max deque
  min_max_likes_.clear();

  // refill min max deque with new reordered linkedlist
  Node<Post *> *temp_node = posts_.getHeadPtr();
  while (temp_node != NULL)
  {
    AddPostForMinMaxLikes(temp_node->getItem());
    temp_node = temp_node->getNext();
  }

  return net_->updateFeed(post);
}

/**
  @post     : Will place post pointers in Linkedlist posts_ into
              corresponding deque based on Priority


        NOTE: Will place all post* into corresponding priority deque,
              within deque, posts will be sorted from Newest(front) to Oldest(back)
*/
void Account::SortPostsIntoDeque()
{
  Node<Post *> *temp = posts_.getHeadPtr();
  while (temp != nullptr)
  {
    if (temp->getItem()->getPriority() == 0)
    {
      low_priority_posts_.push_back(temp->getItem());
    }
    if (temp->getItem()->getPriority() == 1)
    {
      medium_priority_posts_.push_back(temp->getItem());
    }
    if (temp->getItem()->getPriority() == 2)
    {
      high_priority_posts_.push_back(temp->getItem());
    }
    temp = temp->getNext();
  }
}

/**
    @param    : A post pointer
    @post     : Will add newPost to min/max liked deque so that the newest, least liked post is on top
                and oldest, most liked post is in the back.
  */
void Account::AddPostForMinMaxLikes(Post *newPost)
{
  // adding post to min-liked deque, if empty
  if (min_max_likes_.empty())
  {
    min_max_likes_.push_front(newPost);
  }
  else if (newPost->getLikes() <= min_max_likes_.front()->getLikes())
  {
    min_max_likes_.push_front(newPost);
  }
  else if (newPost->getLikes() > min_max_likes_.back()->getLikes())
  {
    min_max_likes_.push_back(newPost);
  }
  else
  {
    std::stack<Post *> temp_stack_;
    // fill temp stack with front values of minmax deque and pop values from deque to keep getting new front
    while (newPost->getLikes() > min_max_likes_.front()->getLikes())
    {
      // add front of deque, to temp stack
      temp_stack_.push(min_max_likes_.front());
      // pop front to get next value
      min_max_likes_.pop_front();
    }
    min_max_likes_.push_front(newPost);
    // empty temp stack into deque to have complete deque again
    while (!temp_stack_.empty())
    {
      // add top of temp stack back to minmax deque
      min_max_likes_.push_front(temp_stack_.top());
      // remove that value from top of stack
      temp_stack_.pop();
    }
  }
}

/**
  @return           :  a pointer to the Post with least likes

  NOTE: YOU MUST DO THIS IN O(1) TIME. Use stack and or queue and add as
        many private members as you need and modify the necessary functions
        and/or add helper functions to do this in O(1) time.

  NOTE: If multiple Posts have the same amount of likes then it should be sorted from Newest to Oldest
        Where in this case it would be the Newest Post with the least amount of likes returned.
*/
Post *Account::getMinLikes() const
{
  return min_max_likes_.front();
}

/**
  @return           :  a pointer to the Post with most likes

  NOTE: YOU MUST DO THIS IN O(1) TIME. Use stack and or queue and add as
        many private members as you need and modify the necessary functions
        and/or add helper functions to do this in O(1) time.

  NOTE: If multiple Posts have the same amount of likes then it should be sorted from Newest to Oldest
        Where in this case it would be the Oldest Post with the most amount of likes returned.
*/
Post *Account::getMaxLikes() const
{
  return min_max_likes_.back();
}

/**
  @return           :  a vector of pointers to Post
  @post             :  the order of the Posts in the vector is by increasing
                       priority, and within each priority class, from oldest
                       to newest

  NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::increasingPriorityOldestToNewest()
{
  // create vector to return ordered posts
  std::vector<Post *> orderedPosts;

  // sort post* in Linked list post_ into corresponding deque
  SortPostsIntoDeque();

  // Loop through 'LOW' Priority, Old to New
  while (!low_priority_posts_.empty())
  {
    orderedPosts.push_back(low_priority_posts_.back());
    low_priority_posts_.pop_back();
  }
  // Loop through 'MEDIUM' Priority, Old to New
  while (!medium_priority_posts_.empty())
  {
    orderedPosts.push_back(medium_priority_posts_.back());
    medium_priority_posts_.pop_back();
  }
  // Loop through 'HIGH' Priority, Old to New
  while (!high_priority_posts_.empty())
  {
    orderedPosts.push_back(high_priority_posts_.back());
    high_priority_posts_.pop_back();
  }

  // return filled vector
  return orderedPosts;
}

/**
  @return           :  a vector of pointers to Post
  @post             :  the order of the Posts in the vector is by increasing
                       priority, and within each priority class, from newest
                       to oldest

  NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::increasingPriorityNewestToOldest()
{
  // create vector to return ordered posts
  std::vector<Post *> orderedPosts;

  // sort post* in Linked list post_ into corresponding deque
  SortPostsIntoDeque();

  // Loop through 'LOW' Priority, New to Old
  while (!low_priority_posts_.empty())
  {
    orderedPosts.push_back(low_priority_posts_.front());
    low_priority_posts_.pop_front();
  }

  // Loop through 'MEDIUM' Priority, New to Old
  while (!medium_priority_posts_.empty())
  {
    orderedPosts.push_back(medium_priority_posts_.front());
    medium_priority_posts_.pop_front();
  }

  // Loop through 'HIGH' Priority, New to Old
  while (!high_priority_posts_.empty())
  {
    orderedPosts.push_back(high_priority_posts_.front());
    high_priority_posts_.pop_front();
  }

  // return filled vector
  return orderedPosts;
}

/**
  @return           :  a vector of pointers to Post
  @post             :  the order of the Posts in the vector is by decreasing
                       priority, and within each priority class, from oldest
                       to newest

  NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::decreasingPriorityOldestToNewest()
{
  // create vector to return ordered posts
  std::vector<Post *> orderedPosts;

  // sort post* in Linked list post_ into corresponding deque
  SortPostsIntoDeque();

  // Loop through 'HIGH' Priority, Old to New
  while (!high_priority_posts_.empty())
  {
    orderedPosts.push_back(high_priority_posts_.back());
    high_priority_posts_.pop_back();
  }

  // Loop through 'MEDIUM' Priority, Old to New
  while (!medium_priority_posts_.empty())
  {
    orderedPosts.push_back(medium_priority_posts_.back());
    medium_priority_posts_.pop_back();
  }

  // Loop through 'LOW' Priority, Old to New
  while (!low_priority_posts_.empty())
  {
    orderedPosts.push_back(low_priority_posts_.back());
    low_priority_posts_.pop_back();
  }

  // return filled vector
  return orderedPosts;
}

/**
  @return           :  a vector of pointers to Post
  @post             :  the order of the Posts in the vector is by decreasing
                       priority, and within each priority class, from newest
                       to oldest

  NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::decreasingPriorityNewestToOldest()
{
  // create vector to return ordered posts
  std::vector<Post *> orderedPosts;

  // sort post* in Linked list post_ into corresponding deque
  SortPostsIntoDeque();

  // Loop through 'HIGH' Priority, New to Old
  while (!high_priority_posts_.empty())
  {
    orderedPosts.push_back(high_priority_posts_.front());
    high_priority_posts_.pop_front();
  }

  // Loop through 'MEDIUM' Priority, New to Old
  while (!medium_priority_posts_.empty())
  {
    orderedPosts.push_back(medium_priority_posts_.front());
    medium_priority_posts_.pop_front();
  }

  // Loop through 'LOW' Priority, New to Old
  while (!low_priority_posts_.empty())
  {
    orderedPosts.push_back(low_priority_posts_.front());
    low_priority_posts_.pop_front();
  }

  // return filled vector
  return orderedPosts;
}
