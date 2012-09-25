#define BALLOON_H

class balloon {
	private:
		double x, y, z, r;
		float cx, cy, cz;
		double slices, stacks;
		float verticies[50][50][3];
		
	public:
		balloon();
		void drawBalloon();
		void topHalf();
		void bottomHalf();
};