#define BALLOON_H

class balloon {
	private:
		double x, y, z, r;
		float cx, cy, cz;
		double slices, stacks;
		///double vertices[50];
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
		struct slice2 slice2[11];
		struct slice1 slice1[11];

		
	public:
		balloon();
		void drawBalloon();
		void topHalf();
		void bottomHalf();
};