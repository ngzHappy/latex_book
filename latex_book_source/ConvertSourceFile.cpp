#include <QtCore/QtCore>
#include <vector>
#include <list>

namespace sstd_convert_source_file{

    namespace sstd_private {

        enum class StringType{
            None,
            Left,
            Right,
            Changed,
        };

        class TypedString  {
        public:
            int start{0};
            int length{0};
            StringType type{StringType::None};
            inline TypedString(int a,int b,StringType c):
                start(a),
                length(b),
                type(c){}
        };

        inline void convertSourceString(const QString & arg,
                                 const QString & argLeft,
                                 const QString & argRight,
                                 std::vector< TypedString > * argAns){
            int varLeft{0};
            for(;;){
                auto varPos = arg.indexOf(  argLeft,varLeft  );
                if(varPos<0){
                    argAns->emplace_back ( varLeft, arg.size()-varLeft   ,StringType::Changed    );
                    return;
                }
                auto varPosEnd =   arg.indexOf( argRight,varLeft  )                     ;
                if(varPos>varLeft){
                    argAns->emplace_back( varLeft ,varPos - varLeft,StringType::Changed  );
                }
                argAns->emplace_back(0,0,StringType::Left);
                argAns->emplace_back(varPos +argLeft.size() ,varPosEnd-varPos-argLeft.size(),StringType::Changed  );
                argAns->emplace_back(0,0,StringType::Right);
                varLeft = varPosEnd+argRight.size();
            }

        }

    }/**/

QString convertSourceString(const QString & arg,
                            const QString & argLeft,
                            const QString & argRight){

    if(arg.isEmpty()){
        return {};
    }

    std::vector< sstd_private::TypedString > data;
    sstd_private::convertSourceString(arg,argLeft,argRight,&data);

    {
        QString ans;
        for(const auto & varI:data){
            if(varI.type == sstd_private::StringType::Changed ){
                ans +=  QStringRef(&arg, varI.start,varI.length ) ;
            }else if(varI.type == sstd_private::StringType::Left){
                ans += argLeft;
            }else if(varI.type == sstd_private::StringType::Right){
                ans += argRight;
            }
        }
        return std::move(ans);
    }

}

}/**/
