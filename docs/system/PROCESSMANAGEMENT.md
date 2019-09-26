# Process management

## Program vs Process vs Threads

## The Process ID

### Process ID allocation

### The Process Hierarchy

### pid_t

### Obtaining the Process ID and Parent Process ID

## Running a New Process

### The Exec Family of Calls

### The fork() System Call

## Terminating a Process

### Other Ways to Terminate

### atexit()

### on_exit()

### SIGHLD

### Waiting for Terminated Child Processes

### Waiting for a Specific Process

### Even More Waiting Versatility

### BSD Wants to Play: wait3() and wait4()

### Launching and Waiting for a New Process

### Zombies

## Users and Groups

### Real, Effective and Saved Users and Group IDs

### Changing the Real or Saved User or Group ID

### Changing the Effective User or Group ID

### Changing the Effective User or Group ID, BSD Style

### Changing the Effective User or Group ID, HP-UX Style

### Preferred User/Group ID Manipulation

### Support for Saved Users IDs

### Obtaining the User and Group IDs

## Sessions and Process Groups

### Session System Calls

### Process Group System Calls

### Obsolete Process Group Functions

## Daemons

## Conclusion