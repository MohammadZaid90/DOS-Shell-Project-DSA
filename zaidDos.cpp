#include<string>
#include<iostream>
#include<ctime>
#include<vector>
#include<list>
#include<windows.h>

using namespace std;
class File
{
public:
    string name;
    string extension;
    string content;
    int size;
    string path;

    File(string name, string extension, string content, string path = "")
    {
        this->name = name;
        this->extension = extension;
        this->content = content;
        this->size = content.length();
    }
};

class Folder
{
public:
	string name;
	vector<Folder*> Folders;
	vector<File*> Files;
	Folder* parent;
	time_t creation_time;
	string owner;
	string path;
	bool hidden;
public:
	Folder(string n = "NULL", string p = "", Folder* parent_ = nullptr, vector<File*> fs = vector<File*>(), vector<Folder*> Fs = vector<Folder*>())
	{
		name = n;
		Folders = Fs;
		Files = fs;
		hidden = false;
		path = p;
		parent = parent_;
	}
	void remove_file(string name)
	{
		for (int i = 0; i < Files.size(); i++)
		{
			if (Files[i]->name == name)
			{
				swap(Files[i],Files[Files.size() - 1]);
				Files.pop_back();
			}
		}
	}
	void remove_folder(string name)
	{
		for (int i = 0; i < Folders.size(); i++)
		{
			if (Folders[i]->name == name)
			{
				swap(Folders[i], Folders[Folders.size() - 1]);
				Folders.pop_back();
			}
		}
	}
	void Emptydir()
	{
		Files.resize(0);
		Folders.resize(0);
	}
	File* Find(string name)
	{
		for (int i = 0; i < Files.size(); i++)
		{
			if (Files[i]->name == name)
			{
				return Files[i];
			}
		}
		return nullptr;
	}
	Folder* FindFolder(string name)
	{
		for (int i = 0; i < Folders.size(); i++)
		{
			if (Folders[i]->name == name)
			{
				return Folders[i];
			}
		}
		return nullptr;
	}
	void InsertFile(File* f)
	{
		Files.push_back(f);
	}
	void InsertFolder(Folder* f)
	{
		Folders.push_back(f);
	}
	void print()
	{
		cout << "Directory of " <<this->path << "\\" << this->name << endl << endl;
		for (auto it = this->Folders.begin(); it != this->Folders.end(); ++it)
		{
			cout << "                            <DIR>         " << (*it)->name << endl;
		}
		for (auto it = this->Files.begin(); it != this->Files.end(); ++it)
		{
			cout << "                                          " << (*it)->name + "." <<(*it)->extension << endl;
		}
	}
	string _GetPath()
    {
        return path;
    }
};

class tree
{
public:
	Folder* root;
	Folder* CF; //Current Folder
public:
	tree()
	{
		root = CF = new Folder("Z");
	}
	void insert(Folder* F)
	{
		CF->Folders.push_back(F);
	}
	void setPath(Folder* F)
	{
		string path = CF->name;
		Folder* parent = new Folder();
		while (parent != nullptr)
		{
			path = parent->name + "/" + path;
			parent = parent->parent;
		}
		F->path = path;
	}
	void print(string prompt = "\\>")
	{
		if (CF->name == "Z")
		{
			cout << "Z:" << prompt;
		}
		else
		{
			cout << "Z:" << CF->path.substr(2, CF->path.length()) << "\\" << CF->name << prompt;
		}
	}
	bool Folder_exists(string name)
	{
		for (int i = 0; i < CF->Folders.size(); i++)
		{
			if (CF->Folders[i]->name == name)
			{
				return true;
			}
			return false;
		}
	}
    bool _IsFileExists(string name)
    {
        for (auto it = this->CF->Files.begin(); it != this->CF->Files.end(); ++it)
        {
            if ((*it)->name == name)
            {
                return true;
            }
        }
        return false;
    }
	File* Find(string name)
	{
		for (int i = 0; i < CF->Files.size(); i++)
		{
			if (CF->Files[i]->name == name)
			{
				return CF->Files[i];
			}
		}
		return nullptr;
	}
	Folder* FindFolder(string name)
	{
		for (int i = 0; CF->Folders.size(); i++)
		{
			if (CF->Folders[i]->name == name)
			{
				return CF->Folders[i];
			}
		}
		return nullptr;
	}
};

class DOS
{
private:
	string lower(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = tolower(str[i]);
		}
		return str;
	}
	bool prompt = false;
public:
	tree t;
	string user = "Zaid";
	DOS()
	{

	}
	void print()
	{
		cout << "\t\t\t" << "Muhammad Zaid | 2022R/2021-CS-214 | DSA-UET-2023 | Sir Muhmmad Faraz" << endl << endl;
		t.print();
	}
	void run()
	{
		print();
		bool exit = false;
		while (!exit)
		{
			exit = input();
		}
	}
	bool input()
	{
		string command;
		getline(cin, command); 
		string opr = command.substr(0, command.find(' '));
		opr = lower(opr);

		if (opr == "mkdir")
		{
			t.insert(new Folder(command.substr(6, command.length()), t.CF->path + "\\" + t.CF->name, t.CF));
		}
		else if (opr == "create")
		{
			string args = command.substr(opr.length() + 1);

			// Find the space after the file name and extension
			size_t pos_space1 = args.find(' ');

			if (pos_space1 != string::npos)
			{
				string fileDetails = args.substr(0, pos_space1);
				string content = args.substr(pos_space1 + 1);

				// Find the dot that separates file name and extension
				size_t pos_dot = fileDetails.find('.');
				if (pos_dot != string::npos)
				{
					string name = fileDetails.substr(0, pos_dot);
					string extension = fileDetails.substr(pos_dot + 1);

					// Create the file using the createFile function
					createFile(name, extension, content);
				}
				else
				{
					cout << "Invalid file name format." << endl;
				}
			}
			else
			{
				cout << "Invalid command format for creating a file." << endl;
			}
		}
		else if (opr == "del")
		{
			t.CF->remove_file(command.substr(4, command.length()));
		}
		else if (opr == "cd")
		{
			string folder = command.substr(3, command.length());
			if (t.Folder_exists(folder))
			{
				t.CF = t.FindFolder(folder);
			}
			else
			{
				cout << "No such directory exists!" << endl;
			}
		}
		else if (opr == "cd..")
		{
			if (t.CF->parent != nullptr)
			{
				t.CF = t.CF->parent;
			}
		}
		else if (opr == "cd\\")
		{
			if (t.CF->parent != nullptr)
			{
				t.CF = t.root;
			}
		}
		else if (opr == "dir" || opr == "cd.")
		{
			t.CF->print();
		}
		else if (opr == "cls")
		{
			system("cls");
			print();
		}
		else if (opr == "exit")
		{
			return true;
		}
		else if (opr == "find")
		{
			string name = command.substr(5, command.length());
			File* f = t.Find(name);
			cout << f->name;
		}
		else if (opr == "format")
		{
			t.CF->Emptydir();
		}
		else if (opr == "rmdir")
		{
			Folder* current = t.CF;
			t.CF = t.CF->parent;
			t.CF->remove_folder(current->name);
		}
		else if (opr == "prompt")
		{
			prompt = !prompt;
		}
		else if (opr == "rename")
		{
			command = command.substr(opr.length() + 1, command.length());
			string currname = command.substr(0, command.find(' '));
			string newname = command.substr(currname.length() + 1, command.length());
			File* f = t.CF->Find(currname);
			f->name = newname;
		}
		else if (opr == "copy")
		{
			command = command.substr(opr.length() + 3, command.length());
			int ind = command.find(' ');
			string sourcepath = command.substr(0, command.find(' '));
			string destpath = command.substr(sourcepath.length() + 3, command.length());
			File * file_to_copy;
			

			Folder * CurrFolder = t.root;
			string f;
			while (sourcepath.length() > 0)
			{
				f = sourcepath.substr(0, sourcepath.find('\\'));
				sourcepath = sourcepath.substr(f.length()+1, sourcepath.length());
				if (sourcepath.length()!=0)
					CurrFolder = CurrFolder ->FindFolder(f);
					if (CurrFolder == nullptr)
					{
						cout << "Path was not found";
						return true;
					}
			}
			file_to_copy = CurrFolder -> Find(f);

			CurrFolder == t.root;
			while (destpath.length() > 0)
			{
				f = destpath.substr(0, destpath.find('\\'));
				destpath = destpath.substr(f.length() + 1, destpath.length());
				CurrFolder = CurrFolder->FindFolder(f);
				if (CurrFolder == nullptr)
				{
					cout << "Path was not found";
					return true;
				}
			}
			CurrFolder->InsertFile(file_to_copy);
		}
		else if (opr == "mov")
		{
			command = command.substr(opr.length() + 3, command.length());
			int ind = command.find(' ');
			string sourcepath = command.substr(0, command.find(' '));
			string destpath = command.substr(sourcepath.length() + 3, command.length());
			File* file_to_mov;

			Folder* CurrFolder = t.root;
			string f;
			while (sourcepath.length() > 0)
			{
				f = sourcepath.substr(0, sourcepath.find(' '));
				sourcepath = sourcepath.substr(f.length() + 1, sourcepath.length());
				if (sourcepath.length() != 0)
					CurrFolder = CurrFolder->FindFolder(f);
				if (CurrFolder == nullptr)
				{
					cout << "Path was not found";
					return true;
				}
			}
			file_to_mov = CurrFolder->Find(f);
			CurrFolder->remove_file(file_to_mov->name);


			CurrFolder = t.root;
			while (destpath.length() > 0)
			{
				f = destpath.substr(0, destpath.find('\\'));
				destpath = destpath.substr(f.length() + 1, destpath.length());
				CurrFolder = CurrFolder->FindFolder(f);
				if (CurrFolder == nullptr)
				{
					cout << "Path was not found";
					return true;
				}
			}
			CurrFolder->InsertFile(file_to_mov);
		}
		else if (opr == "ver")
		{
			cout << "Running Windows 11 Currently" << endl;
		}
		else if (opr == "help")
		{
			help();
		}
		else if (opr == "pwd")
		{
			_PWD();
		}
		if (opr != "cls")
		{
			if (prompt)
				t.print("$");
			else
				t.print();
		}

		return false;
	}
	void createFile(string name, string extension, string content)
	{

		File* file = new File(name, extension, content, t.CF->_GetPath() + name + "." + extension);
		t.CF->InsertFile(file);
	}
	void help()
	{
		cout << "attrib <filename>.<extension>" << endl;
		cout << "cd <directory>" << endl;
		cout << "cd." << endl;
		cout << "cd.." << endl;
		cout << "cd\\" << endl;
		cout << "convert <type1> <type2>" << endl;
		cout << "copy <filename>.<extension> <directory>" << endl;
		cout << "create <filename>.<extension> <content>" << endl;
		cout << "del <filename>.<extension>" << endl;
		cout << "dir" << endl;
		cout << "edit <filename>.<extension> <content>" << endl;
		cout << "exit" << endl;
		cout << "find <filename>" << endl;
		cout << "findf <filename>.<extension> <text>" << endl;
		cout << "findSTR <text>" << endl;
		cout << "format" << endl;
		cout << "help" << endl;
		cout << "loadTree" << endl;
		cout << "mkdir <directory>" << endl;
		cout << "move <filename>.<extension> <directory>" << endl;
		cout << "PPPrint" << endl;
		cout << "prompt" << endl;
		cout << "print <filename>.<extension>" << endl;
		cout << "PQUEUE" << endl;
		cout << "PWD" << endl;
		cout << "QUEUE" << endl;
		cout << "rename <filename>.<extension> <newfilename>.<newextension>" << endl;
		cout << "RMDIR <directory>" << endl;
		cout << "SAVE" << endl;
		cout << "TREE" << endl;
		cout << "VER" << endl;
	}
	void _PWD()
	{

		cout << "\t\t" << t.CF->name << endl;
	}
};

int main()
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 4);

    DOS dosSystem; // Create an instance of the DOS system
    dosSystem.run();

    return 0;
}