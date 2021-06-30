# LevelOne-LED-Arduino

An arduino program to support the Level One art piece by Wesley Scafe.

## The Art

Whenever I think about a social issue and how it could be remedied, the solution never exists in a vacuum. The problem usually has a layer of complexity that requires wider societal change to effectively solve. To pick apart something like factory farming, a practice that is cruel to both the animals involved and the workers who run them, a simple answer would be to ban the practice. No more factory farming. In theory, it’s a good idea, but for those who needed the money from that work, it’s a worse outcome. We also depend on the food they produce in our current system. The same attitude can be applied towards coal mining or logging; both of which involve dangerous work environments and are tied to environmental damage. Taking away these jobs would plunge thousands of individuals into insecure financial positions and cause supply shortages for critical resources. Rather than accept these unjust situations as necessary or too much work to fix, the better solution is to keep digging down until the actual root of the problem is found. In many scenarios, a large obstacle blocking meaningful change is the loss of jobs that comes with reforming a harmful industry. This issue can feasibly be accounted for with the creation of a universal safety net that guarantees food, water, shelter, electricity, and healthcare to everyone.

To universally guarantee these resources would provide a multitude of new freedoms. Parents could choose to stay home and raise their children full-time instead of being forced to work more to support them. Workers could quit jobs that exploit them without the threat of starvation. People could see a doctor when they need to without worrying about the bill. From a broader perspective, harmful industries could be more easily improved without the concern of sending workers into poverty. To enact a policy on this scale would be a huge undertaking both politically and materially, but there is significant evidence that suggests these resources already exist in surplus or would be cheaper under a universal system. The fact that it can be achieved should be reason enough to do so.

![Level One gif](./assets/LevelOne.gif)

## The Program

This program controls 5 LED light strips attached to an arduino uno. The colors transition between 2 predetermined colors per strip and wait between 5 and 8 seconds before transitioning again. The transition takes 2.5 seconds.

### Dependencies

[FastLED](http://fastled.io/)
