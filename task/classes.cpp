#include "classes.hpp"

Mnogougolnik::Mnogougolnik()
{
	std::ifstream f;
	f.open("polys.txt", std::ios::in);
	double x, y;
	char dot;
	if (f.is_open()) {
		while (!f.eof()) {
			f >> x >> dot >> y;
			ugli.push_back(point(x, y));
		}
	}
}
Mnogougolnik::~Mnogougolnik()
{
	ugli.~vector();
}
void Mnogougolnik::print() {
	for (int i = 0; i < ugli.size(); i++) {
		std::cout << "point " << i + 1 << ": (" << ugli[i].x<<", "<<ugli[i].y << ")" << '\n';
	}
}
void Mnogougolnik::check_o(const Otrezki& o1) {
	bool p_in[2];
	std::vector<int> res;

	for (int k = 0; k < o1.otrez.size(); k++) {
		for (int j = 0; j < 2; j++) {
			bool l = false, r= false, t = false , b = false;
			for (int i = 0; i < ugli.size(); i++) {
				/*if (ugli[i].x == o1.otrez[0].p[j].x && ugli[i].x == o1.otrez[0].p[j].y) {
					r = true;
					l = true;
					t = true;
					b = true;
					break;
				}*/
			

				if (ugli[i].x >= o1.otrez[k].p[j].x)
					r = true;
				if (ugli[i].x <= o1.otrez[k].p[j].x)
					l = true;

				if (ugli[i].y >= o1.otrez[k].p[j].y)
					t = true;
				if (ugli[i].y <= o1.otrez[k].p[j].y)
					b = true;

				if (r && l && t && b)
					break;
			}
			if (r && l && t && b)
				p_in[j] = true;
			else
				p_in[j] = false;

			//std::cout<<"result p"<<j<<": " << p_in[j]<<'\n';
		}	
	
		if (p_in[0] && p_in[1]) {
			res.push_back(0);
		}
		else if (p_in[0] || p_in[1])
			res.push_back(2);
		else {
			bool ne_peresek = true;
			double max_x,max_y;
			if (o1.otrez[k].p[0].x >= o1.otrez[k].p[1].x)
				max_x = o1.otrez[k].p[0].x;
			else
				max_x = o1.otrez[k].p[1].x;

			if (o1.otrez[k].p[0].y >= o1.otrez[k].p[1].y)
				max_y = o1.otrez[k].p[0].y;
			else
				max_y = o1.otrez[k].p[1].y;


			for (int i = 0; i < ugli.size() - 1; i++) {
				double min_tmp_x;
				double min_tmp_y;
				if (ugli[i].x <= ugli[i+1].x)
					min_tmp_x = ugli[i].x;
				else
					min_tmp_x = ugli[i+1].x;

				if (ugli[i].y <= ugli[i + 1].y)
					min_tmp_y = ugli[i].y;
				else
					min_tmp_y = ugli[i + 1].y;

				if (max_x > min_tmp_x && max_y > min_tmp_y) {
					double x1 = o1.otrez[k].p[0].x; double x2 = o1.otrez[k].p[1].x;
					double y1 = o1.otrez[k].p[0].y; double y2 = o1.otrez[k].p[1].y;

					double x3 = ugli[i].x; double x4 = ugli[i+1].x;
					double y3 = ugli[i].y; double y4 = ugli[i + 1].y;

					if ((x2 - x1) / (y2 - y1) == (x4 - x3) / (y4 - y3)) {
						res.push_back(3);
					}

					double x = ((x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1)) / ((y1 - y2) * (x4 - x3) - (y3 - y4) * (x2 - x1));
					double y = ((y3 - y4) * x - (x3 * y4 - x4 * y3)) / (x4 - x3);

					if (((x1 <= x) and (x2 >= x) and (x3 <= x) and (x4 >= x)) or ((y1 <= y) and (y2 >= y) and (y3 <= y) and (y4 >= y))) {
						res.push_back(1);
						ne_peresek = false;
					}
				}
				
			}
			if (ne_peresek)
				res.push_back(3);
		}
	}

	std::ofstream F;
	F.open("result.txt", std::ios::out);

	for (int i=0;i<res.size();i++)
		F << res[i]<<"\n";
}



Otrezki::Otrezki() {
	std::ifstream f;
	f.open("lines.txt", std::ios::in);
	double x1, y1, x2, y2;
	char dot;
	if (f.is_open()) {
		while (!f.eof()) {
			f >> x1 >> dot >> y1>>x2 >> dot >> y2;
			otrez.push_back(Otrezok(point(x1, y1), point(x2, y2)));
		}
	}
}
Otrezki::~Otrezki() {
	otrez.~vector();
}
void Otrezki::print() {
	for (int i = 0; i < otrez.size(); i++) {
		std::cout << "otrezok " << i + 1 << ": (" << otrez[i].p[0].x << ", " << otrez[i].p[0].y << ") - (" << otrez[i].p[1].x << ", " << otrez[i].p[1].y << ")" << '\n';
	}
}

