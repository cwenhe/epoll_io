#pragma once

namespace io
{

    class Loop
    {
        public:
            virtual void run() = 0;

            virtual void post() = 0;

            virtual ~Loop()
            {
            }
    };

    
} /* io */ 
