/*
 This example demonstrates how to use OpenCorr to calculate the stain
 according to the polynomial fit displacement fields of u component and
 v component.
*/

#include "opencorr.h"

using namespace opencorr;
using namespace std;

int main() {
	//select the image file to get the file name to process
	string tar_image_path = "../samples/oht_cfrp_4.bmp";
	Image2D tar_img(tar_image_path);

	//get the DIC results from csv file
	IO2D in_out;
	string file_path = tar_image_path + "_sift_icgn2_table.csv";
	in_out.setPath(file_path);
	in_out.setHeight(tar_img.height);
	in_out.setWidth(tar_img.width);
	in_out.setDelimiter(string(","));

	//get time of start
	double timer_tic = omp_get_wtime();

	//set OpenMP parameters
	int cpu_thread_number = omp_get_num_procs() - 1;
	omp_set_num_threads(cpu_thread_number);

	//set the radius of subregion for polynomial fit of displacement field
	int strain_radius = 20;

	//set the miminum number of neighbor POIs to perform fitting
	int min_neighbors = 5;

	//load a queue of POIs
	vector<POI2D> poi_queue = in_out.loadTable2D();

	//initialize a object of stain calculation
	Strain2D* strain = new Strain2D(strain_radius, min_neighbors, poi_queue);

	//calculate the strain exx, exy, eyy
	strain->prepare(poi_queue);
	strain->compute(poi_queue);

	//get time of end
	double timer_toc = omp_get_wtime();
	double consumed_time = timer_toc - timer_tic;

	cout << "Strain calculation: " << consumed_time << " sec" << std::endl;

	//update the table of DIC results with calculated strains
	in_out.saveTable2D(poi_queue);

	//save eyy
	file_path = tar_image_path + "_eyy.csv";
	in_out.setPath(file_path);

	//variable: 'u', 'v', 'c'(zncc), 'd'(convergence), 'i'(iteration), 'f'(feature), 'x' (exx), 'y' (eyy), 'r' (exy)
	in_out.saveMap2D(poi_queue, 'y');

	cout << "Press any key to exit" << std::endl;
	cin.get();

	delete strain;

	return 0;
}