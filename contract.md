## Group Contract for The Cake Whisperers
Melanie	Palmer, AJ (Andrew) Burns, Will Rosenberger, Russell White

### Personal Requirements
#### Meeting Times
All members must attend the following weekly meetings, unless otherwise agreed upon:

* 10 am Tuesday in Cramer
* Meet with Tyler at 11 am on Tuesday
* Dinner and Meeting after Thursday Lab in Somewhere

#### C++
* Follow [Google Style Guide](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html).
* Use in comment TODO for small-scale "to do" things. Use issues for larger issues. TODOs should never reach `dev`.

#### Version Control
* Use Git.
* Commit messages will be structured like this:
```
One line summary (less than 50 characters)

Longer description (wrap at 72 characters)
```
* Commit summary:
  * Less than 50 characters
  *What was changed
  * Write in imperative present tense (fix, add, change):
    (`Fix bug 123.`, `Add 'foobar' command.`, `Change default timeout to 60 seconds.`).
    Ask yourself this question: “What will applying the patch do?”
    and you answer with “it will **remove utils.wrapMethod.**”.
  * Use good grammar, capitalization, etc
* Commit description:
  * Wrap at 72 characters
  * Why, explain intention and implementation approach
  * Present tense
* `master` will only be committed to for releases.
* `dev` is the "active" branch that should be viewed as a release candidate for `master`.
  The only way `master` will be modified is if we are merging `dev` into it.
* All new features and bug fixes should be done in branches from `dev` and then merged back into `dev`.
* Create a pull request on GitHub for all merges and have someone else check the PR before merging.
* Before creating a pull request onto `dev`, use rebase to collapse multiple related commits into single commits.

#### Make System
Use CMake.

#### Testing
* Use Google Test Suite for Unit Testing.
* Use Travis CI for automated testing.

#### Issues
Create an issue to track any new feature or bug fix you are working on. Basically,
  each branch from `dev` should have an issue attached to it. In commit messages, you
  can mention the issue you are working with by just adding (for example) #1 to the
  bottom of the commit.

#### Person-specific
* Personal events will not conflict with the project.
* We will not make Will make will puns or discuss Will's will to update Will's will to make sure it will fully detail Will's last wills.
