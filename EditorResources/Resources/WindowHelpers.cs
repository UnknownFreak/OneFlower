using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace EditorResources.Resources
{
    public class NameValidator : ValidationRule
    {
        public enum ValidationType
        {
            Int,
            Double,
            String,
        }

        public NameValidatorWrapper VerifyAs { get; set; }

        public override ValidationResult Validate
          (object value, System.Globalization.CultureInfo cultureInfo)
        {
            switch (VerifyAs.Value)
            {
                case ValidationType.Int:
                        Int64 i;
                    if (Int64.TryParse(value as string, out i) == false)
                        return new ValidationResult(false, "Integer value required!");
                    break;
                case ValidationType.Double:
                    Double d;
                    if (Double.TryParse(value as string, out d) == false)
                        return new ValidationResult(false, "Floating point value required!");
                    break;
                case ValidationType.String:
                    if ((value as string) == string.Empty)
                        return new ValidationResult(false, "Empty field not allowed.");
                    break;
            }
            return new ValidationResult(true, string.Empty);
        }
    }
    public class NameValidatorWrapper : DependencyObject
    {
        public static readonly DependencyProperty FormatProperty =
             DependencyProperty.Register("Value", typeof(NameValidator.ValidationType),
             typeof(NameValidatorWrapper), new FrameworkPropertyMetadata(NameValidator.ValidationType.String));

        public NameValidator.ValidationType Value
        {
            get { return (NameValidator.ValidationType)GetValue(FormatProperty); }
            set { SetValue(FormatProperty, value); }
        }
    }

    public class BindingProxy : Freezable
    {
        protected override Freezable CreateInstanceCore()
        {
            return new BindingProxy();
        }

        public object Data
        {
            get { return (object)GetValue(DataProperty); }
            set { SetValue(DataProperty, value); }
        }

        public static readonly DependencyProperty DataProperty =
            DependencyProperty.Register("Data", typeof(object), typeof(BindingProxy), new PropertyMetadata(null));

    }
}
