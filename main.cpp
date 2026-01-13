#include <opencv2/opencv.hpp>
#include <deque>

using namespace cv;
using namespace std;

#define FPS 30
#define DELAY_SECONDS 3.1
#define DELAY_FRAMES ((int)(FPS * DELAY_SECONDS))
#define CENTER_MARGIN 20

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) return -1;

    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    Ptr<BackgroundSubtractor> bg = createBackgroundSubtractorMOG2(500, 16, false);
    deque<Mat> buffer;

    Mat frame;
    while (cap.read(frame)) {
        flip(frame, frame, 1);   // same as your Python

        int h = frame.rows;
        int w = frame.cols;
        int mid = w / 2;

        Mat fg, you = Mat::zeros(frame.size(), frame.type());
        Mat her = Mat::zeros(frame.size(), frame.type());

        bg->apply(frame, fg);
        threshold(fg, fg, 40, 255, THRESH_BINARY);
        medianBlur(fg, fg, 7);

        vector<vector<Point>> contours;
        findContours(fg, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (auto &c : contours) {
            if (contourArea(c) > 1200)
                drawContours(you, vector<vector<Point>>{c}, -1,
                             Scalar(255,255,255), 3);
        }

        buffer.push_back(you.clone());
        if (buffer.size() > DELAY_FRAMES)
            buffer.pop_front();

        if (buffer.size() == DELAY_FRAMES) {
            her = buffer.front().clone();
            her.setTo(Scalar(255,0,255), her);
        }

        you(Rect(mid + CENTER_MARGIN, 0,
                 mid - CENTER_MARGIN, h)).setTo(Scalar(0,0,0));

        her(Rect(0, 0,
                 mid - CENTER_MARGIN, h)).setTo(Scalar(0,0,0));

        Mat left, right, output;
        addWeighted(frame, 1.0, you, 1.0, 0, left);
        addWeighted(frame, 1.0, her, 1.0, 0, right);

        hconcat(left(Rect(0,0,mid,h)),
                right(Rect(mid,0,mid,h)),
                output);

        putText(output, "YOU", Point(40,40),
                FONT_HERSHEY_SIMPLEX, 1,
                Scalar(0,255,0), 2);

        putText(output, "HER ???",
                Point(mid + 40,40),
                FONT_HERSHEY_SIMPLEX, 1,
                Scalar(255,0,255), 2);

        imshow("sahiba or delusional gf", output);
        if (waitKey(1) == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
