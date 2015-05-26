/*
// Copyright (c) 2012-2015 Eliott Paris, Julien Colafrancesco, Thomas Le Meur & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_EXCHANGER_LIGHT
#define DEF_HOA_EXCHANGER_LIGHT

#include "Processor.hpp"

namespace hoa
{
    //! The echanger class renumber and normalize the harmonics channels.
    /** The echanger should be used to renumber and normalize the harmonics channels. The library uses the Ambisonics Channels Numbering (ACN), this class allows to convert channels arrengements from Furse-Malham (B-format) or Single Index (SID) to  Ambisonics Channels Numbering (ACN) and conversely. Furse-Malham and SID never reach up to 3rd order so the maximum order of decomposition should be 3. The library uses the semi-normalization (SN2D and SN3D), this class allows to normalize the channels to the full normalization (N2D and N3D) or to MaxN (B-format) and conversely.
     */
    template <Dimension D, typename T> class Exchanger : public Processor<D, T>::Harmonics
    {
    public:
        
        //! The numbering conversion.
        /** The enum defines the numbering conversion.
         */
        enum Numbering
        {
            ACN             = 0, /*!<  The numbering is considered as ACN. */
            fromFurseMalham = 1, /*!<  From Furse-Malham (B-format) to ACN. */
            fromSID         = 2, /*!<  From SID to ACN. */
            toFurseMalham   = 3, /*!<  To Furse-Malham (B-format) from ACN. */
            toSID           = 4  /*!<  To SID from ACN. */
        };
        
        //! The numbering conversion.
        /** The enum defines the numbering conversion.
         */
        enum Normalization
        {
            SN2D            = 0, /*!<  The normalization is considered as semi-normalization. */
            SN3D            = 0, /*!<  The normalization is considered as semi-normalization. */
            fromN2D         = 0, /*!<  From N2D to SN2D. */
            fromN3D         = 0, /*!<  From N3D to SN3D. */
            fromMaxN        = 1, /*!<  From MaxN (B-format) to SN2D/SN3D. */
            toN2D           = 2, /*!<  To N2D from SN2D. */
            toN3D           = 2, /*!<  To N3D from SN3D. */
            toMaxN          = 3  /*!<  To MaxN (B-format) from SN2D/SN3D. */
        };

        //! The exchanger constructor.
        /**	The exchanger constructor allocates and initialize the member values to renumber and normalize the harmonics channels. The order must be at least 1 and should be 3 at maximum.
         @param     order	The order.
         */
        Exchanger(const ulong order) noexcept = 0;

        //! The exchanger destructor.
        /**	The exchanger destructor free the memory.
         */
        virtual ~Exchanger() noexcept;

        //! This method performs the numbering and the normalization.
        /**	You should use this method for in-place or not-in-place processing and sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         @param     inputs   The inputs array.
         @param     outputs  The outputs array.
         */
        virtual void process(T const* inputs, T* outputs) noexcept;
        
        //! Sets the numbering conversion.
        /**	This method sets the numbering conversion.
         @param mode The numbering convertion.
         */
        virtual void setNumbering(const Numbering mode) noexcept;
        
        //! Gets the numbering conversion.
        /**	This method gets the numbering conversion.
         @return The numbering convertion.
         */
        virtual Numbering getNumbering(const Numbering mode) const noexcept;
    };

#ifndef DOXYGEN_SHOULD_SKIP_THIS

    template <typename T> class Exchanger<Hoa2d, T> : public Processor<Hoa2d, T>::Harmonics
    {
    public:
        //! The numbering conversion.
        /** The enum defines the numbering conversion.
         */
        enum Numbering
        {
            ACN             = 0, /*!<  The numbering is considered as ACN. */
            fromFurseMalham = 1, /*!<  From Furse-Malham (B-format) to ACN. */
            fromSID         = 2, /*!<  From SID to ACN. */
            toFurseMalham   = 3, /*!<  To Furse-Malham (B-format) from ACN. */
            toSID           = 4  /*!<  To SID from ACN. */
        };
        
        //! The numbering conversion.
        /** The enum defines the numbering conversion.
         */
        enum Normalization
        {
            SN2D            = 0, /*!<  The normalization is considered as semi-normalization. */
            fromN2D         = 0, /*!<  From N2D to SN2D. */
            fromMaxN        = 1, /*!<  From MaxN (B-format) to SN2D. */
            toN2D           = 2, /*!<  To N2D from SN2D. */
            toMaxN          = 3  /*!<  To MaxN (B-format) from SN2D. */
        };
        
    private:
        Numbering       m_numbering;
        Normalization   m_normalization;
    public:

        //! The exchanger constructor.
        /**	The exchanger constructor allocates and initialize the member values to renumber and normalize the harmonics channels. The order must be at least 1 and should be 3 at maximum.
         @param     order	The order.
         */
        inline Exchanger(const ulong order) noexcept : Processor<Hoa2d, T>::Harmonics(order),
        m_numbering(ACN),
        m_normalization(SN2D)
        {
            ;
        }
        
        //! The exchanger destructor.
        /**	The exchanger destructor free the memory.
         */
        inline ~Exchanger() noexcept
        {
            ;
        }
        
        //! Sets the numbering and the normalization conversion from B-Format.
        /**	This method the numbering and the normalization conversion from B-Format. Similar to from Furse-Malham numebring and from MaxN normalization.
         */
        inline void setFromBFormat() noexcept
        {
            m_numbering = fromFurseMalham;
            m_normalization = fromMaxN;
        }
        
        //! Sets the numbering and the normalization conversion to B-Format.
        /**	This method the numbering and the normalization conversion from B-Format. Similar to to Furse-Malham numebring and to MaxN normalization.
         */
        inline void setToBFormat() noexcept
        {
            m_numbering = toFurseMalham;
            m_normalization = toMaxN;
        }
        
        //! Sets the numbering conversion.
        /**	This method sets the numbering conversion.
         @param mode The numbering convertion.
         */
        inline void setNumbering(const Numbering mode) noexcept
        {
            m_numbering = mode;
        }
        
        //! Gets the numbering conversion.
        /**	This method gets the numbering conversion.
         @return The numbering convertion.
         */
        inline Numbering getNumbering() const noexcept
        {
            return m_numbering;
        }
        
        //! Sets the normalization conversion.
        /**	This method sets the normalization conversion.
         @param mode The normalization convertion.
         */
        inline void setNormalization(const Normalization mode) noexcept
        {
            m_normalization = mode;
        }
        
        //! Gets the normalization conversion.
        /**	This method gets the normalization conversion.
         @return The normalization convertion.
         */
        inline Normalization getNormalization() const noexcept
        {
            return m_normalization;
        }
        
        //! This method performs the numbering and the normalization.
        /**	You should use this method for in-place or not-in-place processing and sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         @param     inputs   The inputs array.
         @param     outputs  The outputs array.
         */
        void process(T const* inputs, T* outputs) noexcept
        {
            switch(m_normalization)
            {
                    
            }
            switch(m_numbering)
            {
                case fromFurseMalham:
                    numberFromFurseMalham(inputs, outputs);
                    break;
                case fromSID:
                    numberFromSID(inputs, outputs);
                    break;
                case toFurseMalham:
                    numberToFurseMalham(inputs, outputs);
                    break;
                case toSID:
                    numberToSID(inputs, outputs);
                    break;
            }
        }
        
        //! This method number the channels from Furse-Malham to ACN.
        /**	You should use this method for in-place or not-in-place processing and sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         @param     inputs   The inputs array.
         @param     outputs  The outputs array.
         */
        void numberFromFurseMalham(T const* inputs, T* outputs) noexcept
        {
            T temp = inputs[1];
            *(outputs++) = inputs[0]; // W -> 0
            *(outputs++) = inputs[2]; // Y -> 1
            *(outputs++) = temp;      // X -> 2
            if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 1ul)
            {
                T temp       = inputs[3];
                *(outputs++) = inputs[4]; // V -> 3
                *(outputs++) = temp;      // U -> 4
                if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 2ul)
                {
                    T temp       = inputs[5];
                    *(outputs++) = inputs[6]; // Q -> 5
                    *(outputs++) = temp;      // U -> 6
                }
            }
        }
        
        //! This method number the channels from SID to ACN.
        /**	You should use this method for in-place or not-in-place processing and sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         @param     inputs   The inputs array.
         @param     outputs  The outputs array.
         */
        void numberFromSID(T const* inputs, T* outputs) noexcept
        {
            T temp = inputs[1];
            *(outputs++) = inputs[0]; // W -> 0
            *(outputs++) = inputs[2]; // 2 -> 1
            *(outputs++) = temp;      // 1 -> 2
            if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 1ul)
            {
                T temp       = inputs[3];
                *(outputs++) = inputs[4]; // 4 -> 3
                *(outputs++) = temp;      // 3 -> 4
                if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 2ul)
                {
                    T temp       = inputs[5];
                    *(outputs++) = inputs[6]; // 6 -> 5
                    *(outputs++) = temp;      // 5 -> 6
                }
            }
        }
        
        //! This method number the channels from ACN to Furse-Malham.
        /**	You should use this method for in-place or not-in-place processing and sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         @param     inputs   The inputs array.
         @param     outputs  The outputs array.
         */
        void numberToFurseMalham(T const* inputs, T* outputs) noexcept
        {
            T temp = inputs[1];
            *(outputs++) = inputs[0]; // 0 -> W
            *(outputs++) = inputs[2]; // 2 -> X
            *(outputs++) = temp;      // 1 -> Y
            if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 1ul)
            {
                T temp       = inputs[3];
                *(outputs++) = inputs[4]; // 4 -> U
                *(outputs++) = temp;      // 3 -> V
                if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 2ul)
                {
                    T temp       = inputs[5];
                    *(outputs++) = inputs[6]; // 6 -> U
                    *(outputs++) = temp;      // 5 -> Q
                }
            }
        }
        
        //! This method number the channels from ACN to SID.
        /**	You should use this method for in-place or not-in-place processing and sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         @param     inputs   The inputs array.
         @param     outputs  The outputs array.
         */
        void numberToSID(T const* inputs, T* outputs) noexcept
        {
            T temp = inputs[1];
            *(outputs++) = inputs[0]; // 0 -> W
            *(outputs++) = inputs[2]; // 2 -> 1
            *(outputs++) = temp;      // 1 -> 2
            if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 1ul)
            {
                T temp       = inputs[3];
                *(outputs++) = inputs[4]; // 4 -> 3
                *(outputs++) = temp;      // 3 -> 4
                if(Processor<Hoa3d, T>::Harmonics::getDecompositionOrder() > 2ul)
                {
                    T temp       = inputs[5];
                    *(outputs++) = inputs[6]; // 6 -> 5
                    *(outputs++) = temp;      // 5 -> 6
                }
            }
        }
    };

#endif
}

#endif


