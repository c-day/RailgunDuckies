#define BALLOON_H

class balloon {
	private:
		double x, y, z, r;
		struct slice1 {
			double x; 
			double y;
			double z;
		};
		struct slice2 {
			double x;
			double y;
			double z;
		};
		struct slice2 slice2[41];
		struct slice1 slice1[41];

		
	public:
		balloon();
		void drawBalloon();
		void topHalf();
		void bottomHalf();
};