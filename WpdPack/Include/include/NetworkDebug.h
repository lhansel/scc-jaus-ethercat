#ifdef __cplusplus 
extern "C"
{
#endif

	void InitializeNetworkGDB();
    void InitializeNetworkGDB_and_Wait(); 


#define BREAKPOINT() asm("   trap #2");

class  dbip_obj
{
const char * cp;
public: dbip_obj(const char *x);
};


#define DebugIP(x)                static  dbip_obj dbip_obj1(x);
#define DebugRebootOnTrap()       static  dbip_obj dbip_obj2("RT"); 
#define DebugRebootOnDisconnect() static  dbip_obj dbip_obj3("RD");  
#define DebugNormalArp()          static  dbip_obj dbip_obj4("A");  


#ifdef __cplusplus
};
#endif



