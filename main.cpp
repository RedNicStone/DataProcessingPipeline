#include <iostream>
#include <gnuplot-iostream.h>
#include <rapidcsv.h>
#include <vector>


int main() {
    rapidcsv::Document doc("data/Damped_mass_on_spring_LONG.csv");

    std::vector<float> pos = doc.GetColumn<float>("Velocity (m/s)");
    std::vector<float> time = doc.GetColumn<float>("Time (s)");

    std::cout << "There are " << pos.size() << " data points that have been read" << std::endl;

    Gnuplot gp;
    // For debugging or manual editing of commands:
    //Gnuplot gp(std::fopen("plot.gnu"));
    // or
    //Gnuplot gp("tee plot.gnu | gnuplot -persist");


    // Min, Mean, Max
    std::tuple<float, float, float> rangePos = { pos[0],
                                                 pos[0],
                                                 pos[0], };
    std::tuple<float, float, float> rangeTime = { time[0],
                                                  time[0],
                                                  time[0] };

    std::vector<std::pair<double, double> > xy_pts;
    for(size_t i = 0; i < 20 * 180; i++) {
        xy_pts.emplace_back(time[i], pos[i]);

        rangePos = { std::min(std::get<0>(rangePos), pos[i]),
                     std::get<1>(rangePos) + pos[i] / static_cast<float>(pos.size()),
                     std::max(std::get<2>(rangePos), pos[i]) };
        rangeTime = { std::min(std::get<0>(rangeTime), time[i]),
                      std::get<1>(rangeTime) + time[i] / static_cast<float>(time.size()),
                      std::max(std::get<2>(rangeTime), time[i]) };
    }

    std::get<0>(rangePos) -= std::get<1>(rangePos);
    std::get<2>(rangePos) -= std::get<1>(rangePos);
    for (auto& valuePair : xy_pts) {
        valuePair.second -= std::get<1>(rangePos);
    }

    gp << "set xrange [" << std::get<0>(rangeTime) << ":" << std::get<2>(rangeTime) << "]\n"
          "set yrange [" << std::get<0>(rangePos) << ":" << std::get<2>(rangePos) << "]\n";
    gp << "plot '-' with points title 'position'\n";
    gp.send1d(xy_pts);
}
