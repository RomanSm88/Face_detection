#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <QtGui>
#include <QTime>
#include "ui_face_detection.h"
#include <opencv2\opencv.hpp>
#include <algorithm>

using namespace cv;

class Face_detection : public QWidget
{
	Q_OBJECT

public:
	Face_detection(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Face_detection();



private:
	Ui::Face_detectionClass ui;
	// ��������� ��� �������� ��������������� �����, ������� ����� ��������� �� �����
	CascadeClassifier *haar_cascade;
	// ��������� �� ���� � ���������������
	const char *haarcascade_frontalface_alt2;
	// ��������� �� �����-����
	VideoCapture *file;
	// ������� ���������-������ ��� �������� �������� ����� �����.
	QList<CvScalar> colors;
	// ��������� - ������, �� ����������� ���������� STL, ��� �������� ��������� ����, ���������������� �� �����������
	vector<Rect> vector_objekt; // ��� ������� ������������, ��� R��, �.� - ��� ������, �������� �������� �������� ���������, ������������ 2x2
	// ��������� �� ������ �����������
	QImage *qimage;
	// ��������� �� ������ ���������� Qt ��� ������ ����������� - QPixmap
	QPixmap *qpix;
	double height_pix, width_pix;
	QTimer *time;
	QTimer *fps_time;
	QTime *time_zaderjka;
	string fileName;
	// ������������ ������ ��������� ���������
	int fps_summ;
	// ����� ������ ��������� ���������
	int fps_detect;
	// ����� ���������� ������������� ��������
	void en_ds_knopci(bool znach);
	// ����� ��������� ��������������� ��� ���������� ����� � ������
	void stop_video();
	// �������� ����� ��������� �����������
	void face_search(Mat &src, Mat &temp, double =720.0, double =480.0);
	void face_search(Mat &src, double =720.0, double =480.0);
	// ����� �������� �������� �����������
	bool proverka_otkrxtiy();
	// ������� ���� ��� ������ ����������� ����� ��������� ����������� openCV
	private slots:
		void on_actionCapture_opencv();
		void on_actionCapture_opencv_camera();
		void knopka_play();
		void knopka_obzor();
		void fps_count();
		void radio_button_fail();
		void radio_button_camera();
};

#endif // FACE_DETECTION_H
