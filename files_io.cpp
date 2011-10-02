#include "files_io.h"

void save_image(cimg_library::CImg<double> output, int i){
    string outname = "output-";
    stringstream ss;
    ss << i;
    outname.append(ss.str());
    outname.append(".bmp");
    output.save(outname.c_str());
}
cimg_library::CImg<double> get_psf(void){
    //load image
    cimg_library::CImg<double> temp_psf_img("psf.bmp");
    cimg_library::CImg<double> psf_img(3,3,1,1,0);

    //cimg_forXY(temp_psf_img,x,y) {
    //    psf_img(x,y,0,0) = temp_psf_img(x,y,0,0);
    //}
    psf_img(0,0,0,0) = 0.1070;
    psf_img(1,0,0,0) = 0.1131;
    psf_img(2,0,0,0) = 0.1070;
    psf_img(0,1,0,0) = 0.1131;
    psf_img(1,1,0,0) = 0.1196;
    psf_img(2,1,0,0) = 0.1131;
    psf_img(0,2,0,0) = 0.1070;
    psf_img(1,2,0,0) = 0.1131;
    psf_img(2,2,0,0) = 0.1070;
    
    return psf_img;
}

cimg_library::CImg<double> get_image(vector<string> files, int i){
    string path = files[i];

    //load image
    cimg_library::CImg<double> temp_img(path.c_str());
    //cimg_library::CImg<double> img(1024,1024,1,1,0);

    //cimg_forXY(img,x,y) {
    //    img(x,y,0,0) = temp_img(x,y,0,0);
    //}

    return temp_img;
}

bool has_ending (std::string const &fullString, std::string const &ending){
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool get_dir (string dir, vector<string> *files){
DIR *dp;
struct dirent *dirp;
if((dp = opendir(dir.c_str())) == NULL) {
    return false;
}

while ((dirp = readdir(dp)) != NULL) {
    if(has_ending(string(dirp->d_name), ".bmp")){
        files->push_back(string(dirp->d_name));
    }
}
closedir(dp);
return true;
}

bool init_images(vector<string> *files){
    string dir = string(".");
    return get_dir(dir,files);
}