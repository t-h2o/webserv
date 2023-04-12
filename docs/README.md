# WEBSERVER

## CGI (common getaway interface)
### methods

* `GET`: the methode `GET` are the most common used methods in APIs and website. `GET` **is used to retrieve data from a server
at the specified resource**.
  * Example: You have an API with a `/user` endpoint (Endpoints are physical devices that connect to and exchange
  information with a computer network). Making a `GET` request to that endpoint should return a list of all available users.
  * `GET` is only requesting data and not modifying any ressources.


* When you creating test for an API, the `GET` method is the most frequent type of request made by consumers of the 
  service, it's important to **check every known endpoint with a GET request**.


* At a basic level, these things should be validated.
  * check that a valid `GET` request return a 200 status code.
  * Ensure that a `GET` request return the correct data for the specific resource.
    * Example: GET/users return a list of users


* `GET` is often the **default method in HTTP clients**, creating test is simple with any tools.