/* isnan example 
The NaN values are used to identify undefined or non-representable values for floating-point elements, 
such as the square root of negative numbers or the result of 0/0.
*/
#include <stdio.h>      /* printf */
#include <math.h>       /* isnan, sqrt */

int main(){
  printf ("isnan(0.0)       : %d\n",isnan(0.0));
  printf ("isnan(1.0/0.0)   : %d\n",isnan(1.0/0.0));
  printf ("isnan(-1.0/0.0)  : %d\n",isnan(-1.0/0.0));
  printf ("isnan(sqrt(-1.0)): %d\n",isnan(sqrt(-1.0)));
  return 0;
}
