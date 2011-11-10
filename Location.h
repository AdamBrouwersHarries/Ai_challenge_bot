#ifndef LOCATION_H_
#define LOCATION_H_

/*
    struct for representing locations in the grid.
*/
struct Location
{
    int row, col;
    Location()
    {
        row = col = 0;
    };

    Location(int r, int c)
    {
        row = r;
        col = c;
    };
	bool operator!= (Location param) {
		if(this->row!=param.row or this->col!=param.col)
		{
			return false;
		}else
		{
			return true;
		}
	}
};

#endif //LOCATION_H_
