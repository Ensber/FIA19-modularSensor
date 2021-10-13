<?php


namespace App\Exception;


use Exception;

class InputValidationException extends Exception
{
    private array $validationErrors;

    public function __construct(array $validationErrors, $message = "")
    {
        $this->validationErrors = $validationErrors;
        parent::__construct($message);
    }


    /**
     * @return string[]
     */
    public function getValidationErrors(): array
    {
        return $this->validationErrors;
    }



}