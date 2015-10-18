#include <mi/SvgRenderer.hpp>

int main ( int argc, char** argv ) {
	mi::SvgRenderer renderer ( 300, 300, "test.svg");
	renderer.setViewBox( -2, -2, 2, 2);
	
	renderer.setStrokeColor("red");
	renderer.drawLine(-1.5, -1.5, -1.5, 1.5);
	renderer.setStrokeColor("blue");
	renderer.drawLine(-1.5, 1.5, 1.5, 1.5);
	renderer.setStrokeColor("yellow");
	renderer.drawLine(1.5, 1.5, 1.5, -1.5);
	renderer.setStrokeColor("green");
	renderer.drawLine(1.5, -1.5, -1.5, -1.5);
	renderer.drawText(0, 0, "test");
	// automatically saved
	return 0;
}
