#ifndef MYCASH_H
#define MYCASH_H


class MyCash{
private:
    static MyCash* _inst;
    int user_id=0;
    MyCash(){
    }
    static MyCash* instance(){
        if(!_inst)
            _inst = new MyCash();
        return _inst;
    }
public:
    static void set_user_id(int id){
        instance()->user_id = id;
    }
    static int get_user_id(){
        return instance()->user_id;
    }
};


#endif // MYCASH_H
