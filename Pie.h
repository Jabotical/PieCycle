#ifndef PIE_H_
#define PIE_H_

class Pie {
public:
	enum Type
	{
		Pecan,
		Apple,
		PBChocolate,
		Rhubarb
	};


	Pie(Pie::Type type);
	virtual ~Pie();

	bool isCoolEnoughToEat();
	void cool(double degreesCToCool);
	Type getType();


private:
	Type _type;
	double _temperatureCelcius;

	const double _bakedTempCelcius 	= 200;
	const double _edibleTempCelcius = 30;
	const double _roomTempCelcius 	= 20;
};

#endif /* PIE_H_ */
