# cse2102-Lab5

the first step to getting it running is to clone the repo

ex: `git clone https://github.com/AdrianG0954/cse2102-Lab5.git `

once you have cloned the repo you can change your directory to the one of the project

ex: `cd Lab5` and once done we do `cd demo`

at this point we are in the right directory and we can set our variables.

we need to set the java_home variable as follows

`JAVA_HOME="/usr/"` then `export JAVA_HOME` and finally we can build using `./mvnw package`

if you are getting a permission denied error you can solve this by running the following command

`chmod +x mvnw`

now we can run tests if necessary using `./mvnw test` and we can run it using 

`./mvnw spring-boot:run`

after it will show you a popup to open in browser and then the quiz will display
