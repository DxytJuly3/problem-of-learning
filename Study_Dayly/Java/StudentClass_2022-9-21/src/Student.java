public class Student {
	private static int StudentCount = 0;
	private int Age;
	private String Name;
	private String StuID;
	private String Gender;

	public Student(String _StuID, String _Name, String _Gender, int _Age) {
		Name = _Name;
		StuID = _StuID;
		Age = _Age;
		Gender = _Gender;
		StudentCount++;
	}
	
	public void setName(String _Name) {
		Name = _Name;
	}
	public void setStuID(String _StuID) {
		StuID = _StuID;
	}
	public void setAge(int _Age) {
		Age = _Age;
	}
	public void setGender(String _Gender) {
		Gender = _Gender;
	}

	public String getName() {
		return Name;
	}
	public String getStuID() {
		return StuID;
	}
	public int getAge() {
		return Age;
	}
	public String getGender() {
		return Gender;
	}
	public static int getStudentCount() {
		return StudentCount;
	}
	
	public String toString() {
		String retStr;
		retStr = "学号： " + StuID + "  姓名： " + Name + "  性别： " + Gender + "  年龄： " + Age;
		
		return retStr;
	}
}
